import sys
from typing import List


def parse_rules(rules: List[str]):
    d = {}
    for rule in rules:
        name, eqn = rule[:-1].split('{')
        eqns = eqn.split(",")
        length = len(eqns)
        eqns = [(x[0], x[1], *x[2:].split(":")) if index + 1 < length else x for index, x in enumerate(eqns)]
        d[name] = eqns
    return d

def parse_workflow(workflow: str):
    workflow = workflow[1:-1]
    values = {x[0]: int(x[2:]) for x in workflow.split(",")}
    return values


rules = []

while True:
    line = sys.stdin.readline().strip()
    if len(line) <= 0:
        break
    rules.append(line)
rules = parse_rules(rules)

workflows = [line.strip() for line in sys.stdin.readlines()]
ans = 0


def process(workflow: List[str], rulename: List[List[str]]):
    if rulename == "A" or rulename == "R":
        return rulename == "A"
    
    length = len(rules[rulename])
    for i in range(length - 1):
        var, symbol, value, label = rules[rulename][i]
        if (symbol == "<" and workflow[var] < int(value)) or (symbol == ">" and workflow[var] > int(value)):
            if label == "A":
                return True
            if label == "R":
                return False
            return process(workflow, label)
    
    return process(workflow, rules[rulename][-1])

for workflow in workflows:
    workflow = parse_workflow(workflow)
    result = process(workflow, "in")

    if result:
        for v in workflow.values():
            ans += v

print(f"Day 19 (Part 1): {ans}")
