#include <iostream>
#include <cmath>
#include "queue.h"
#include <cstdlib>

using namespace std;

int main()


// Cur time problema zapusti i prover'
{
    int NUMBER_OF_REQUESTS=1000;
    int SHOW_HISTORY=100;
    srand(45);
    int out=0;
    int in=0;
    double wt=0;

    queue* head=NULL;
    double cur_time=0;
    double time_service;
    double work_time=0;
    double wait_time=0;

    queue* cur_service=NULL;
    queue* m=NULL;

    double time=-1;


    double in_beg,in_end,serv_beg,serv_end;
    cin>>in_beg>>in_end>>serv_beg>>serv_end;

    while(out<NUMBER_OF_REQUESTS){
        if (time<0){
            time=cur_time+(rand()/double(RAND_MAX))*(in_end-in_beg)+in_beg;
            time_service=(serv_end-serv_beg)*rand()/double(RAND_MAX)+serv_beg;
            //cout<<time<<"\n\n";
        }
        if (cur_service){
                //cout<<cur_time<<" "<<time<<" "<<cur_service->left_service<<"\n\n";
                if (cur_time+cur_service->left_service>time){
                    push(head,time,time_service,in+1);
                    //cout<<head->id<<"\n";
                    //cout<<"sosi";
                    in++;
                    cur_service->left_service-=(time-cur_time);
                    increment(head,time-cur_time);
                    cur_time=time;
                    time=-1;
                }else if(cur_time+cur_service->left_service<time){
                    increment(head,cur_service->left_service);
                    cur_time+=cur_service->left_service;
                    cur_service->loop++;
                    cur_service->left_service=cur_service->service;
                    if (cur_service->loop==4){
                            work_time+=4*cur_service->service;
                            wait_time+=cur_service->wait_time;

                        out++;
                        if (!m || m->wait_time<cur_service->wait_time){
                            m=cur_service;
                        }else{
                        delete(cur_service);}
                        cur_service=NULL;
                        if (out%SHOW_HISTORY==0 && out!=NUMBER_OF_REQUESTS){
                                queue* m1=max_wait(head);
                                wt=wait(head)+wait_time;
                                if (m1 && m1->wait_time>m->wait_time){
                                    cout<<in<<" "<<len(head)<<" "<<" "<<m1->id<<" "<<m1->loop<<" "<<m1->wait_time<<" "<<wt/in<<"\n";
                                }else{

                            cout<<in<<" "<<len(head)<<" "<<" "<<m->id<<" "<<m->loop<<" "<<m->wait_time<<" "<<wt/in<<"\n";}
                        }
                    }else{
                    add_to_tail(head,cur_service);
                    cur_service=NULL;
                    }

                    cur_service=pop(head);
                }
                else{
                    push(head,time,time_service,in+1);
                    in++;
                    cur_service->left_service-=(time-cur_time);
                    increment(head,time-cur_time);
                    cur_time=time;
                    time=-1;
                    cur_service->loop++;
                    cur_service->left_service=cur_service->service;
                    if (cur_service->loop==4){
                        work_time+=4*cur_service->service;
                        wait_time+=cur_service->wait_time;
                        out++;
                        if (!m || m->wait_time<cur_service->wait_time){
                            m=cur_service;
                        }else{
                        delete(cur_service);}
                        cur_service=NULL;
                        if (out%SHOW_HISTORY==0 && out!=NUMBER_OF_REQUESTS){
                                queue* m1=max_wait(head);
                                wt=wait_time+wait(head);
                                if (m1 && m1->wait_time>m->wait_time){
                                    cout<<in<<" "<<len(head)<<" "<<" "<<m1->id<<" "<<m1->loop<<" "<<m1->wait_time<<" "<<wt/in<<"\n";
                                }else{

                            cout<<in<<" "<<len(head)<<" "<<" "<<m->id<<" "<<m->loop<<" "<<m->wait_time<<" "<<wt/in<<" "<<"\n";}
                        }
                    }else{
                    add_to_tail(head,cur_service);
                    cur_service=NULL;

                    }
                    cur_service=pop(head);
                }



        }
        else{
            if (head){
                cur_service=pop(head);
            }
            else {
                push(head,time,time_service,in+1);
                //cout<<head->id<<"\n";
                in++;
                cur_time=time;
                time=-1;
            }

        }



    }

work_time+=work(head);
cout<<cur_time<<" "<<cur_time-work_time<<" "<<in<<" "<<out<<"\n";

}
