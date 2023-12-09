#ifndef RULE_MANAGER_H
#define RULE_MANAGER_H

#define MAX_RULES 100
#define MAX_RULE_NAME 64
#define MAX_CONDITION 64

typedef struct {
    char rule_name[MAX_RULE_NAME];
    char condition[MAX_CONDITION];
} Rule;

typedef struct {
    Rule rules[MAX_RULES];
    int count;
} RuleManager;

void init_rule_manager(RuleManager* rule_manager);
void add_rule(RuleManager* rule_manager, const char* rule_name, const char* condition);
void delete_rule(RuleManager* rule_manager, const char* rule_name);
void update_rule(RuleManager* rule_manager, const char* rule_name, const char* new_condition);
void read_rules_from_file(RuleManager* rule_manager, const char* filename);

#endif
