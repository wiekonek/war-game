#ifndef ATTACK_H
#define	ATTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "msg.h"

typedef struct {
    GtkButton *button_attack;
} AttackWindow;

int attack_run(GtkBuilder *builder, int id);

#endif	/* ATTACK_H */

