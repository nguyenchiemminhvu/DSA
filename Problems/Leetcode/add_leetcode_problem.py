import sys
import os

if __name__ == "__main__":
    # get list of problem in the current directory
    problems = [f for f in os.listdir()]

    # https://leetcode.com/problems/sample-problem-name/
    problem_link = sys.argv[1]
    problem_name = problem_link.split("/")[4]
    # standardize the problem name by removing hyphens, Uppercase first letters
    problem_name = problem_name.replace("-", " ").title().replace(" ", "")
    if problem_name in problems:
        print(f"Problem '{problem_name}' already exists.")
    else:
        os.mkdir(problem_name)
        with open(os.path.join(problem_name, "solve.py"), "w") as f:
            f.write(f"# Solution for {problem_name}\n")
        with open(os.path.join(problem_name, "explain.md"), "w") as f:
            f.write(f"## Problem\n\n{problem_link}\n\n```\n```\n\n## Observations\n\n## Solution\n\n# Tags\n\n")
        print(f"Problem '{problem_name}' has been created.")
