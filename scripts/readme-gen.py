import os
import argparse

languages = ["c", "cpp", "python", "java", "rust", "javascript"]


def generate_readme(year):
    readme_content = ""
    readme_content += f"| month | {' | '.join(languages)} |\n"
    readme_content += f"| --- | {'--- | ' * len(languages)}\n"

    for day in sorted(os.listdir(year)):
        day_path = os.path.join(year, day)
        if os.path.isdir(day_path):
            solutions = []
            for lang in languages:
                solution = get_solution_link(day_path, lang)
                solutions.append(solution)

            row = f"| {day} | {' | '.join(solutions)} |\n"
            readme_content += row

    return readme_content

def get_solution_link(day_path, language):
    language_path = os.path.join(day_path, language)
    if os.path.exists(language_path):
        return f"[✔️]({language_path})"
    else:
        return "-"

def main():
    parser = argparse.ArgumentParser(description="Generate README table for solutions.")
    parser.add_argument("--year", type=str, help="Year for which to generate the README table", required=True)
    args = parser.parse_args()

    readme = generate_readme(args.year)
    print(f"README table generated for {args.year}")
    print("-" * 80)
    print(readme)

if __name__ == "__main__":
    main()
