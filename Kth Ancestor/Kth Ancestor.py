import sys
from collections import defaultdict, namedtuple
from array import array


AddNode = namedtuple('AddNode', 'child parent')
RemoveNode = namedtuple('RemoveNode', 'node')
QueryParent = namedtuple('QueryParent', 'node kth')


def log(msg):
    print(msg, file=sys.stderr)


def find_all_leaf_nodes(tree):
    queue = set([0, ])
    while queue:
        node = queue.pop()
        if node in tree.children:
            for c in tree.children[node]:
                queue.add(c)
        else:
            yield node


def solve_queries(tree, queries):
    #log('Tree:')
    #print_tree(tree)
    for q in queries:
        #log(q)
        if type(q) == AddNode:
            tree.add_node(q.child, q.parent)
        elif type(q) == RemoveNode:
            tree.remove_leaf(q.node)
        elif type(q) == QueryParent:
            yield tree.get_kth_parent(q.node, q.kth)


def read_ints(reader):
    for p in (_.strip().split() for _ in reader):
        yield tuple([int(_) for _ in p])


class Tree(object):
    def __init__(self):
        self.children = defaultdict(set)
        self.parents = dict()
        self.levels = dict()
        self.levels[0] = 0
        self.ten_p = dict()
        self.hundred_p = dict()
        self.thousand_p = dict()
        self.cache_hits = [0, 0, 0]

    def add_node(self, child, parent):
        # first get the level
        level = self.levels[parent] + 1
        self.levels[child] = level
        self.children[parent].add(child)
        self.parents[child] = parent
        if level > 10 and level % 10 == 0:
            self.ten_p[child] = self.get_kth_parent(child, 10)
        if level > 100 and level % 100 == 0:
            self.hundred_p[child] = self.get_kth_parent(child, 100)
        if level > 1000 and level % 1000 == 0:
            self.thousand_p[child] = self.get_kth_parent(child, 1000)

    def remove_leaf(self, node):
        level = self.levels.pop(node)
        parent = self.parents.pop(node)
        self.children[parent].remove(node)
        if level % 10 == 0:
            try:
                self.ten_p.pop(node)
            except KeyError:
                pass
        if level % 100 == 0:
            try:
                self.hundred_p.pop(node)
            except KeyError:
                pass
        if level % 1000 == 0:
            try:
                self.thousand_p.pop(node)
            except KeyError:
                pass

    def get_kth_parent(self, node, max_back):
        if node not in self.parents:
            return 0
        if self.levels[node] < max_back:
            return 0
        zero_counter = max_back
        while node != 0 and zero_counter != 0:
            if zero_counter > 1000 and node in self.thousand_p:
                self.cache_hits[2] += 1
                node = self.thousand_p[node]
                zero_counter -= 1000
                continue
            if zero_counter > 100 and node in self.hundred_p:
                self.cache_hits[1] += 1
                node = self.hundred_p[node]
                zero_counter -= 100
                continue
            if zero_counter > 10 and node in self.ten_p:
                self.cache_hits[0] += 1
                node = self.ten_p[node]
                zero_counter -= 10
                continue
            node = self.parents[node]
            zero_counter -= 1
        # we are at the root-root node
        return node


def read_instructions(int_lines):
    number_cases = next(int_lines)[0]
    for _ in range(number_cases):
        nodes_in_tree = next(int_lines)[0]
        tree = Tree()
        for pos, (child, parent) in enumerate(int_lines):
            tree.add_node(child, parent)
            if pos == nodes_in_tree - 1:
                break
        number_queries = next(int_lines)[0]
        queries = list()
        for pos, vals in enumerate(int_lines):
            if vals[0] == 0:
                # notice reversal, to make same as input
                queries.append(AddNode(vals[2], vals[1]))
            elif vals[0] == 1:
                queries.append(RemoveNode(vals[1]))
            elif vals[0] == 2:
                queries.append(QueryParent(vals[1], vals[2]))
            else:
                raise Exception('Do not know how to handle query of type %d in %s' % (vals[0], vals))
            if pos == number_queries - 1:
                break
        yield (tree, queries)


def main():
    for tree, queries in read_instructions(read_ints(sys.stdin)):
        for answer in solve_queries(tree, queries):
            print(answer)
    log('Cached: %s' % (tree.cache_hits))


if __name__ == '__main__':
    main()
