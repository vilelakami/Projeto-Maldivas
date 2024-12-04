#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <stdbool.h>

#define MAX_DIALOGUES 5

typedef struct {
    const char* texto;
} Dialogue;

typedef struct {
    Dialogue dialogues[MAX_DIALOGUES];
    int dialogue_index;
    bool dialogue_finished;
} DialogueManager;

void init_dialogues(Dialogue* dialogues);
void init_dialogue_manager(DialogueManager* manager);

#endif // DIALOGUE_H
