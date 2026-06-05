#include <stdio.h>

int main() {
    int pages, frames, i, j;
    int pageFaults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &pages);

    int ref[pages];

    printf("Enter page reference string:\n");
    for(i = 0; i < pages; i++)
        scanf("%d", &ref[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    int frame[frames];

    for(i = 0; i < frames; i++)
        frame[i] = -1;

    int index = 0;

    for(i = 0; i < pages; i++) {
        int found = 0;

        for(j = 0; j < frames; j++) {
            if(frame[j] == ref[i]) {
                found = 1;
                break;
            }
        }

        if(!found) {
            frame[index] = ref[i];
            index = (index + 1) % frames;
            pageFaults++;
        }
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);

    return 0;
}
