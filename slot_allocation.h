#ifndef SLOT_ALLOCATION_H
#define SLOT_ALLOCATION_H

int find_nearest_available_slot();
int mark_slot_occupied(int slot_no);
int mark_slot_available(int slot_no);

#endif // SLOT_ALLOCATION_H
