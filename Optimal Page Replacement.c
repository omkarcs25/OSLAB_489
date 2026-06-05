#include <stdio.h>

int main() {
    int pages, frames, i, j, k;
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

    for(i = 0; i < pages; i++) {
        int found = 0;

        for(j = 0; j < frames; j++) {
            if(frame[j] == ref[i]) {
                found = 1;
                break;
            }
        }

        if(!found) {
            int pos = -1;
            int farthest = i;

            for(j = 0; j < frames; j++) {
                int nextUse;

                for(nextUse = i + 1; nextUse < pages; nextUse++) {
                    if(frame[j] == ref[nextUse])
                        break;
                }

                if(nextUse == pages) {
                    pos = j;
                    break;
                }

                if(nextUse > farthest) {
                    farthest = nextUse;
                    pos = j;
                }
            }

            if(pos == -1)
                pos = 0;

            frame[pos] = ref[i];
            pageFaults++;
        }
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);

    return 0;
}
