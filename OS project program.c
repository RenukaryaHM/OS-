/*
 ------------------------------------------------------------
 Simple Batch Job Scheduler
 Operating Systems Project
 Scheduling Policy : First-Come, First-Served (FCFS)

 Features:
 1. Accepts jobs with submission time and run time
 2. Simulates batch processing
 3. Maintains job table
 4. Calculates throughput
 ------------------------------------------------------------
*/

#include <stdio.h>

/* Structure to represent a job */
struct Job {
    int jobId;
    int submissionTime;
    int runTime;
    int startTime;
    int completionTime;
};

/* Function to sort jobs based on submission time (FCFS) */
void sortJobs(struct Job jobs[], int n) {
    struct Job temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (jobs[i].submissionTime > jobs[j].submissionTime) {
                temp = jobs[i];
                jobs[i] = jobs[j];
                jobs[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    int currentTime = 0;

    printf("Enter number of jobs: ");
    scanf("%d", &n);

    struct Job jobs[n];

    /* Input job details */
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Job %d\n", i + 1);
        jobs[i].jobId = i + 1;

        printf("Submission Time: ");
        scanf("%d", &jobs[i].submissionTime);

        printf("Estimated Run Time: ");
        scanf("%d", &jobs[i].runTime);
    }

    /* Sort jobs based on submission time */
    sortJobs(jobs, n);

    /* Scheduling simulation */
    for (int i = 0; i < n; i++) {

        /* If CPU is idle, move time to job submission */
        if (currentTime < jobs[i].submissionTime) {
            currentTime = jobs[i].submissionTime;
        }

        jobs[i].startTime = currentTime;
        jobs[i].completionTime = currentTime + jobs[i].runTime;

        currentTime = jobs[i].completionTime;
    }

    /* Display Job Table */
    printf("\n---------------- Job Table ----------------\n");
    printf("JobID\tSubmit\tStart\tComplete\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n",
               jobs[i].jobId,
               jobs[i].submissionTime,
               jobs[i].startTime,
               jobs[i].completionTime);
    }

    /* Throughput Calculation */
    float totalTime = jobs[n - 1].completionTime - jobs[0].submissionTime;
    float throughput = n / totalTime;

    printf("\nTotal Execution Time: %.2f", totalTime);
    printf("\nThroughput: %.2f jobs/unit time\n", throughput);

    return 0;
}
