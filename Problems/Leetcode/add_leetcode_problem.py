import sys
import os

if __name__ == "__main__":
    # get list of problem in the current directory
    problems = [f for f in os.listdir()]

    # https://leetcode.com/problems/sample-problem-name/
    problem_link = sys.argv[1]
    problem_name = problem_link.split("/")[4]
    commit_message = f"leetcode problem: {problem_name.replace('-', ' ').title()}"
    # standardize the problem name by removing hyphens, Uppercase first letters
    folder_name = problem_name.replace("-", " ").title().replace(" ", "")
    if folder_name in problems:
        print(f"Problem '{folder_name}' already exists.")
    else:
        os.mkdir(folder_name)
        with open(os.path.join(folder_name, "solve.py"), "w") as f:
            f.write(f"# Solution for {problem_name}\n")
        with open(os.path.join(folder_name, "explain.md"), "w") as f:
            f.write(f"## Problem\n\n{problem_link}\n\n```\n```\n\n## Observations\n\n## Solution\n\n# Tags\n\n")
        print(f"Problem '{folder_name}' has been created.")

    chr = ''
    while chr not in ['','n','N', 'y','Y']:
        chr = input("Enter 'y' to continue pushing changes to git, or type 'n' to skip: ")
        if chr.lower() == 'y':
            os.system("git add --all")
            os.system(f'git commit -m "{commit_message}"')
            os.system("git push origin master")
            break
        elif chr.lower() == 'n':
            print("Skipping git push.")
            break