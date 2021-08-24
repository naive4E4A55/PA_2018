#include "common.h"
#include "x86.h"

#define NR_IRQ_HANDLE 32

/* There are no more than 16(actually, 3) kinds of hardward interrupts. */
#define NR_HARD_INTR 16

struct IRQ_t {
	void (*routine)(void);
	struct IRQ_t *next;
};

static struct IRQ_t handle_pool[NR_IRQ_HANDLE];
static struct IRQ_t *handles[NR_HARD_INTR];
static int handle_count = 0;

void do_syscall(TrapFrame *);

void
add_irq_handle(int irq, void (*func)(void) ) {
	assert(irq < NR_HARD_INTR);
	assert(handle_count <= NR_IRQ_HANDLE);

	struct IRQ_t *ptr;
	ptr = &handle_pool[handle_count ++]; /* get a free handler */
	ptr->routine = func;
	ptr->next = handles[irq]; /* insert into the linked list */
	handles[irq] = ptr;
}
extern volatile int has_ide_intr;
void irq_handle(TrapFrame *tf) {
	int irq = tf->irq;
	//Log("has_ide_intr=%d,irq=%d\n",has_ide_intr,irq);
	//Log("irq=%d\n",irq);
	if (irq < 0) {
		panic("Unhandled exception!");
	} else if (irq == 0x80) {
		do_syscall(tf);
	} else if (irq < 1000) {
		panic("Unexpected exception #%d at eip = %x", irq, tf->eip);
	} else if (irq >= 1000) {
		int irq_id = irq - 1000;
		assert(irq_id < NR_HARD_INTR);

		//if(irq_id == 0) panic("You have hit a timer interrupt, remove this panic after you've figured out how the control flow gets here.");
		//Log("in irq\n");		
		//BREAK_POINT;
		//extern void ide_intr();
		//ide_intr();
		struct IRQ_t *f = handles[irq_id];
		//has_ide_intr=1;
		while (f != NULL) { /* call handlers one by one */
			//Log("f!=NULL\n");
			f->routine(); 
			f = f->next;
			
		}
		//has_ide_intr=1;
	}
}

