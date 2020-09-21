/******************************************************************************

            Assignment # 2

Course: CPSC 3380
Author: Jonathan Haskett
Date: 09/21/2020

Program name: OSAssignment2

*******************************************************************************/

#include <iostream>
#include <ctime>
#include <cmath>
#include <limits>
#include "pcb.h"

struct saved_regs* alloc_saved_regs() {
    struct saved_regs* reg = (struct saved_regs*)malloc(sizeof(struct saved_regs));
    reg->reg1 = rand() % INT_MAX;
    reg->reg2 = rand() % INT_MAX;
    reg->reg32 = rand() % INT_MAX;
    reg->reg_pc = rand() % INT_MAX;
    return reg;
}

struct pcb_type* create_new_pcb() {
    struct pcb_type* new_pcb = (struct pcb_type*)malloc(sizeof(struct pcb_type));
    new_pcb->proc_id = rand() % 100;
    new_pcb->proc_priority = rand() % 20;
    new_pcb->proc_state = rand() % 3;
    new_pcb->proc_class = 1;
    new_pcb->reg_pt = alloc_saved_regs();
    return new_pcb;
}

void add_new_process(struct pcb_type* pcb) {
    if (!start) {
        start = (struct process_list*) malloc(sizeof(struct process_list));
        start->pcb_pt = pcb;
        start->who_follows = NULL;
    }

    else {
        struct process_list* tmp = start;

        while (tmp->who_follows) {
            tmp = tmp->who_follows;
        }

        struct process_list* new_process = (struct process_list*)malloc(sizeof(struct process_list));
        new_process->pcb_pt = pcb;
        new_process->who_follows = NULL;
        tmp->who_follows = new_process;
    }
}

void print_details() {
    srand(time(NULL));
    struct process_list* tmp = start;
    int i = 0;
    while(tmp) {
        printf("index of process: %d\n", ++i);
        int addr_pcb = tmp->pcb_pt->reg_pt->reg1 + tmp->pcb_pt->reg_pt->reg2 + tmp->pcb_pt->reg_pt->reg32 + tmp->pcb_pt->reg_pt->reg_pc;
        printf("addr_pcb = %x\n", addr_pcb);
        printf("proc_id = %d\n", tmp->pcb_pt->proc_id);
        printf("proc_class = %d\n", tmp->pcb_pt->proc_class);
        printf("proc_priority = %d\n", tmp->pcb_pt->proc_priority);
        printf("proc_state = %d\n\n", tmp->pcb_pt->proc_state);
        tmp = tmp->who_follows;
    }
}


int main()
{
    struct pcb_type* p1;
    int i = 0;
    for (i = 0; i < 12; i++)
    {
        p1 = create_new_pcb();
        add_new_process(p1);
    }
    print_details();
    return 0;
}
