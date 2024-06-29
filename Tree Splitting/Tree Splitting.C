#include <stdlib.h>
#include <stdio.h>

struct Set {
    int count;
};

typedef struct Set Set;

struct node{
    int number;
    struct node * parent;
    struct node * next;
    struct node * prev;
    struct node * first_child;
    Set * set;
};

typedef struct node node;

void print_children(node * n){
    node * child = n->first_child;
    while(child){
        printf("%d\n", child->number);
        child = child->next;
    }
}

void add_child(node * n, node * c){
    node * cur = n->first_child;
    n->first_child = c;
    if (cur){
        cur->prev = c;
        c->next = cur;
    }
}

void fill_children(node * root, node ** nodes, node ** result_nodes){
    node * repr = nodes[root->number];
    if(repr == 0){
        return;
    }
    node * child = repr->first_child;
    while(child){
        if (result_nodes[child->number] != 0){
            child = child->next;
            continue;
        }
        node * c = calloc(1, sizeof(node));
        c->number = child->number;
        c->parent = root;
        result_nodes[c->number] = c;
        add_child(root, c);
        fill_children(c, nodes, result_nodes);
        child = child->next;
    }
}

void compute_below(node * root, Set * set) {
    if (set == 0) {
        set = calloc(1, sizeof(set));
    }
    root->set = set;
    set->count++;
    node * child = root -> first_child;
    while(child){
        compute_below(child, set);
        child = child->next;
    }
}

void remove_node(node * item) {
//    subtract_below(item, item->below+1);
    int everyChild = item->parent != 0;
    node * child = item->first_child;
    int childCount = 0;
    int toRemove = 1;
    while (child) {
        childCount++;
        if (everyChild || childCount > 1) {
            compute_below(child, 0);
            toRemove += child->set->count;
        }
        child->parent = 0;
        child = child->next;
    }
    item->set->count -= toRemove;
    node * parent = item->parent;
    if(parent){
        if(parent->first_child == item){
            parent->first_child = item->next;
        }
        if(item->next){
            item->next->prev = item->prev;
        }
        if(item->prev){
            item->prev->next = item->next;
        }
    }
}

int main(int argc, char **argv){
    int n;
    scanf("%d\n", &n);
    int i = 0;
    node ** nodes = calloc(n+1, sizeof(node *));
    for(i = 0; i < n-1; i++){
        int a,b;
        scanf("%d %d\n", &a, &b);
        node * node_a = nodes[a];
        if(node_a == 0) {
            node_a = calloc(1, sizeof(node));
            node_a->number = a;
            nodes[a] = node_a;
        }
        node * x = calloc(1, sizeof(node));
        x->number = b;
        add_child(node_a,x);
        
        node * node_b = nodes[b];
        if(node_b == 0){
            node_b = calloc(1, sizeof(node));
            node_b->number = b;
            nodes[b] = node_b;
        }
        x = calloc(1, sizeof(node));
        x->number = a;
        add_child(node_b, x);
    }
    
    node * root = calloc(1, sizeof(node));
    root->number = 1;
    node ** result_nodes = calloc(n+1, sizeof(node *));
    result_nodes[1] = root;
    fill_children(root, nodes, result_nodes);
    compute_below(result_nodes[1], 0);
    int ans = 0;
    int num_queries;
    scanf("%d\n", &num_queries);
    for(i = 0; i < num_queries; i++){
        int m;
        scanf("%d\n", &m);
        int q = m^ans;
        node * n = result_nodes[q];
        ans = n->set->count;
        printf("%d\n", ans);
        remove_node(n);
    }
    return 0;
}
