import os
import argparse

def generate_readme(year):
    readme_content = ""
    readme_content += "| month | c | c++ | python |\n"
    readme_content += "| --- | --- | --- | --- |\n"

    for day in sorted(os.listdir(year)):
        day_path = os.path.join(year, day)
        if os.path.isdir(day_path):
            c_solution = get_solution_link(day_path, "c")
            cpp_solution = get_solution_link(day_path, "cpp")
            python_solution = get_solution_link(day_path, "python")

            row = f"| {day} | {c_solution} | {cpp_solution} | {python_solution} |\n"
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
