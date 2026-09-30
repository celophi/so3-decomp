#!/usr/bin/env python3
"""Fetch optional, pinned analysis tools without changing the development image."""

import argparse
import hashlib
import json
from pathlib import Path
import stat
import tarfile
import urllib.request
import zipfile

ROOT = Path(__file__).resolve().parents[1]
LOCK = ROOT / 'config/analysis-tools.json'


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def records():
    return json.loads(LOCK.read_text())['downloads']


def checked_file(path):
    relative = str(Path(path).relative_to(ROOT)) if Path(path).is_absolute() else str(path)
    record = next(r for r in records() if r['path'] == relative)
    result = ROOT / relative
    if not result.is_file() or sha256(result.read_bytes()) != record['sha256']:
        raise ValueError(f'{relative}: missing or changed; run python tools/analysis_tools.py '
                         f'--tool {record.get("group", "sdk")}')
    return result


def setup(group="sdk"):
    exclude = ROOT / '.git/info/exclude'
    text = exclude.read_text()
    for rule in ('/tools/ccc/', '/tools/ghidra-emotionengine-reloaded/', '/tools/m2c/', '/working/'):
        if rule not in text.splitlines():
            text += '\n' + rule + '\n'
    exclude.write_text(text)
    for record in records():
        if record.get("group", "sdk") != group:
            continue
        path = ROOT / record['path']
        if not path.is_file() or sha256(path.read_bytes()) != record['sha256']:
            data = urllib.request.urlopen(record['url'], timeout=60).read()
            if sha256(data) != record['sha256']:
                raise ValueError(f'{record["path"]}: download hash mismatch')
            path.parent.mkdir(parents=True, exist_ok=True)
            temporary = path.with_suffix(path.suffix + '.tmp')
            temporary.write_bytes(data)
            temporary.replace(path)
        if path.suffix == '.zip':
            with zipfile.ZipFile(path) as archive:
                for entry in archive.infolist():
                    destination = (path.parent / entry.filename).resolve()
                    if not destination.is_relative_to(path.parent.resolve()):
                        raise ValueError('archive member escapes tool directory')
                    archive.extract(entry, path.parent)
                    if not entry.is_dir():
                        mode = (entry.external_attr >> 16) & 0o777
                        destination.chmod(mode or 0o644)
            executable = path.parent / 'ccc_v2.1_linux-musl/stdump'
            executable.chmod(executable.stat().st_mode | stat.S_IXUSR)
        elif path.name.endswith('.tar.gz'):
            with tarfile.open(path) as archive:
                archive.extractall(path.parent, filter='data')
        print(f'Checked {record["path"]}')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--tool', choices=('sdk', 'm2c'), default='sdk')
    args = parser.parse_args()
    setup(args.tool)


if __name__ == '__main__':
    main()
