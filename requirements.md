MASTERCHEF MANAGEMENT SOFTWARE
==============================

# GENERAL FEATURES

* Add, edit, delete MASTERCHEFs.
* Save managed MASTERCHEFs a specified file.
* Load managed MASTERCHEFs from a specified file.
* Display managed MASTERCHEFs in tabular format (descending order: name, salary)
* Search for a MASTERCHEF by name, by specialization or within a salary range
* Calculate the total spending on employees' salaries.

# MASTERCHEF GENERAL DATA STRUCTURE

* Name: string, sentence capitalization
* Date of Birth: string, "YYYY/MM/DD" format
* Hiring Date: string, "YYYY/MM/DD" format
* Monthly Salary: integer
* Specialization: MASTER CHEF > SEASONED CHEF > JUNIOR CHEF > APPRENTICE COOK

# MASTERCHEF DATABASE FILE FORMAT

Managed MASTERCHEFs will be saved in a `.chefs` file. Each line in the file will represent a single chef.
```
NAME: "CHEF NAME", DOB: "YYYY/MM/DD", HIRED: "YYYY/MM/DD", SALARY: "1000000"
```

Additionally, the first few lines in the file will list out the some of the following details:
```
OWNER: "OWNER NAME"
DATEFORMAT: "YYYY/MM/DD"
CURRENCY: "<currency symbol>"
```
