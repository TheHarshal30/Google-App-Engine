#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct Job{
    char id;
    int deadline, profit;

    Job(char id, int deadline,int profit) : id(id), deadline(deadline), profit(profit){}

};

class JobScheduler{
private:
    vector<Job> jobs;
public:
    void addJob(char id, int deadline, int profit){
        jobs.push_back({id,deadline,profit});
    }
    
    void scheduleJobs(){
        sort(jobs.begin(), jobs.end(), [](Job a, Job b){
            return a.profit > b.profit;
        });

        vector<char> results;
        vector<bool> slot(jobs.size(), false);

        for(auto job: jobs){
            for(int i = min((int)jobs.size()-1, job.deadline-1); i>=0; i--){
                if(!slot[i]){
                    results.push_back(job.id);
                    slot[i] = true;
                    break;
                }
            }
        }

        cout << "Job schedule for maximum profits:" << endl;
        for(auto id: results){
            cout << id << " ";
        }
        cout << endl;
    }
};

int main(){
     JobScheduler scheduler;

    // Add jobs to the scheduler
    scheduler.addJob('a', 2, 100);
    scheduler.addJob('b', 1, 19);
    scheduler.addJob('c', 2, 27);
    scheduler.addJob('d', 1, 25);
    scheduler.addJob('e', 3, 15);

    // Find the maximum profit job sequence
    scheduler.scheduleJobs();
    return 0;
}