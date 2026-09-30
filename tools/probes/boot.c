/* Compiler probes reconstructed from the verified US boot executable.
 * Names describe addresses, not recovered original symbols. */

void *probe_00101250(char *object)
{
    return object + 0x15a24;
}

void *probe_00101510(unsigned int *object)
{
    int i;
    for (i = 0; i < 16; i++) {
        object[i + 16] = 0;
    }
    return object;
}

int probe_0010a080(int *object, int *value)
{
    if (*value > 0) {
        object[44] = 1;
        return *value;
    }
    return 0;
}

int probe_0010a0b0(int *object, int *value)
{
    if (*value > 0) {
        object[68] = 1;
        object[43] = 1;
        return *value;
    }
    return 0;
}

struct ProbeQueue {
    volatile int write_index;
    int read_index;
    void *items[1024];
};

int probe_0011ee00(struct ProbeQueue *queue, void *value)
{
    if (!value) {
        return 1;
    }
    if (queue->read_index == queue->write_index) {
        return 0;
    }
    queue->items[queue->write_index++] = value;
    if (queue->write_index >= 1024) {
        queue->write_index = 0;
    }
    return 1;
}
