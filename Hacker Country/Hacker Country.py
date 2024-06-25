#!/bin/python3

import os
import sys


def hackerCountry(tolls):
    lc = len(tolls)
    k = [i for i in range(lc)]

    class Hiker:
        def __init__(self, tolls: list):
            self.cities = tolls
            self.min_p = [200,1]
            self.min_ratio = self.min_p[0]/self.min_p[1]
            self.valid_paths = {}
            self.time_in_copy_1 = 0
            self.time_in_copy_2 = 0
            self.time_in_copy_3 = 0
            self.paths_added = 0
            self.best_path = []
            self.it = range(lc)
            self.it2 = [x for x in ["road","toll","is_over"]]
            self.iterations = 0
            self.possible_paths = []
        def find_start_path_for_city(self, city: int):
            self.valid_paths[city] = []
            for i, c in enumerate(self.cities[city]):
                # print(i,c,city)
                path = {"toll": 0, "road": 0, "path": [city], "is_over": False, "lookup":{}}
                if i != city:
                    # path.increase(self.cities[city][c],c)
                    path["path"].append(i)
                    path["road"] += 1
                    path["toll"] += c
                    path["lookup"][i]=""

                    self.valid_paths[city].append(path)
                    # find return path
                    if (path["toll"] + self.cities[i][city]) / (
                            path["road"] + 1) < self.min_ratio:
                        self.min_p[0] = path["toll"] + self.cities[i][city]
                        self.min_p[1] = path["road"] + 1
                        self.min_ratio = self.min_p[0] / self.min_p[1]


        def expand_path(self, path: dict,city:int,):
            if path["toll"] / path["road"] > self.min_ratio:
                path["is_over"] = True
            while not path["is_over"]:
                #pp = self.get_path(path)
                pp = path["path"]
                start_len = len(pp)
                for c in self.it:
                    if c not in path["lookup"]:

                        path["road"] += 1
                        t= self.cities[pp[-1]][c]
                        path["toll"] += t
                        pp.append(c)
                        if path["toll"] / path["road"] < self.min_ratio:
                            cities_left = list(set(pp[1:] + k))
                            tolls_left = [self.cities[c][_] for _ in
                                          cities_left]
                            if (min(tolls_left) + path["toll"]) / (path["road"] + 1) < self.min_ratio:

                                path_new = {x: path[x] for x in self.it2}
                                path_new["path"]=pp.copy()
                                path_new["lookup"]=path["lookup"].copy()
                                path_new["lookup"][c]=""
                                self.valid_paths[city].append(path_new)
                                if (path["toll"] + self.cities[c][city]) / (
                                        path["road"] + 1) < self.min_ratio:
                                    self.min_p[0] = path["toll"] + \
                                                    self.cities[c][
                                                        city]
                                    self.min_p[1] = path["road"] + 1
                                    self.min_ratio = self.min_p[0]/self.min_p[1]

                        path["toll"]-=t
                        path["road"]-=1
                        pp.pop(-1)
                if len(pp) == start_len:
                    path["is_over"] = True


        def check_paths_for_city(self, city: int):
            finalized_paths = 0
            while finalized_paths < len(self.valid_paths[city]):
                finalized_paths = 0
                for i, p in enumerate(self.valid_paths[city]):
                    if p["is_over"]:
                        finalized_paths += 1
                    else:
                        self.expand_path(p,city)

        def find_best_ratio(self, a: int, b: int):
            # print(f"original res {a}/{b}")
            y = 10
            while True:
                to_break = True
                for i in range(y, 1, -1):
                    if a % i == 0 and b % i == 0:
                        a = a // i
                        b = b // i
                        y = i
                        to_break = False
                if to_break:
                    break
            return (f"{a}/{b}")

        def main(self):
            for c in self.it:
                self.find_start_path_for_city(c)
            for c in self.it:
                self.check_paths_for_city(c)
            return self.find_best_ratio(self.min_p[0], self.min_p[1])

    h = Hiker(tolls)
    return h.main()


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input())

    tolls = []

    for _ in range(n):
        tolls.append(list(map(int, input().rstrip().split())))

    result = hackerCountry(tolls)

    fptr.write(result + '\n')

    fptr.close()
