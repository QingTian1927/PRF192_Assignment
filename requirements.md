MASTERCHEF MANAGEMENT SOFTWARE
==============================

# General Features

* Add, edit, delete MASTERCHEFs.
* Save managed MASTERCHEFs a specified file.
* Load managed MASTERCHEFs from a specified file.
* Display managed MASTERCHEFs in a table.
* Search for a MASTERCHEF by name or within a salary range
* Calculate the total spending on employees' salaries.

# Masterchef General Data Structure

* Name: string, sentence capitalization
* Date of Birth: string, "YYYY/MM/DD" format
* Monthly Salary: integer
* Role: MASTER CHEF > SEASONED CHEF > JUNIOR CHEF > APPRENTICE COOK

# Masterchef Database File Format

Managed MASTERCHEFs will be saved in a `.chefs` file. Each line in the file will represent a single chef.
```
NAME:CHEF NAME,ROLE:CHEF ROLE,DOB:YYYY/MM/DD,SALARY:1000000
```
