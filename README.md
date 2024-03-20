# I. Tính năng

* Thêm, xóa & sửa thông tin của đầu bếp.
* Đọc và lưu danh sách đầu bếp vào file.
* Hiện toàn bộ danh sách đầu bếp theo dạng bảng.
* Tìm đầu bếp theo tên hoặc là theo mức lương.
* Tính tổng tiền lương của toàn bộ đầu bếp.

# II. Cấu trúc tổng quan

Nhìn chung, Phần mềm quản lý _masterchef_ (_Masterchef Management Software_) được cấu tạo từ những thành phần sau:

1. Masterchef Manager
2. Chef List
3. Chef Object
4. Database
5. Date Parser
6. String Format
7. User Interface

Mỗi bộ phận sẽ chịu trách nhiệm cho một số chức năng nhất định trong phần mềm tổng thể. Chức năng của một hoặc nhiều bộ phận có thể được liên kết chặt chẽ với nhau nhưng vẫn đảm bảo sao cho mỗi bộ phận có thể hoạt động một cách độc lập (_ít nhất là hết mức có thể_)

## 1. Masterchef Manager

Đây là phần _driver code_ của chương trình. Nói cách khác, đây là phần code chịu trách nhiệm liên kết toàn bộ các bộ phận khác với nhau để cấu tạo nên chương trình tổng thể.

## 2. Chef List

Đây là phần chịu trách nhiệm cho việc khởi tạo và tương tác với các danh sách đầu bếp. Phần lớn những chức năng liên quan đến danh sách đầu bếp đầu bếp như là sắp xếp, xóa bỏ, kiểm tra trạng thái, vv, đều nằm trong phần này.

## 3. Chef Object

Bộ phận này định nghĩa cấu trúc dữ liệu cụ thể tượng trưng cho từng đầu bếp một. Mọi thứ liên quan đến việc truy cập và cập nhật
thông tin trong hồ sơ đầu bếp đều phải thông qua bộ phận này.

## 4. Database

Đây là bộ phận sử dụng để đọc và lưu danh sách đầu bếp vào một file nào đó trong máy tính, đảm bảo rằng dữ liệu được xử lý phải tuân theo đúng định dạng.

## 5. Date Parser

Đây là một bộ phận nhỏ chịu trách nhiệm cho việc phân tích cú pháp của một xâu thời gian (_ví dụ: 2024-03-13_) và đảm bảo rằng đây là một xâu hợp lệ (_ví dụ: 2000-02-29 hợp lệ nhưng 2001-02-29 thì không_).

## 6. String Format

Tương tự như Date Parser, đây là một bộ phận con sử dụng để biến đổi xâu theo một định dạng nhất định. Ví dụ:

```
/* dữ liệu gốc - chú ý cả dấu cách lẫn lộn */

loReM    ipSUM  DoloR SIT    AMEt, COnsECTeTur   AdIpiSCiNg ELit

/* dữ liệu sau khi biến đổi */

Lorem Ipsum Dolor Sit Amet, Consectetur Adipiscing Elit
```

## 7. User Interface

Như cái tên của nó, bộ phận này chịu trách nhiệm cho mảng giao diện người dùng. Nói cách khác, bộ phận này chịu trách nhiệm trình bày thông tin tới người dùng.

# III. Chi tiết kỹ thuật

## 1. Cấu trúc dữ liệu đầu bếp

### 1.1 Thuộc tính

* `name`: string, in hoa chữ cái đầu từng từ, dấu cách chuẩn chỉnh.

* `role`: string, một trong những giá trị sau: MASTER CHEF > SEASONED CHEF > JUNIOR CHEF > APPRENTICE COOK

* `dateOfBirth`: string, định dạng YYYY-MM-DD

* `salary`: long integer

``` c
// Bao gồm dấu kết rỗng (null terminator)
#define ACTUAL_MAX_NAME_LEN 31
#define ACTUAL_MAX_DATE_LEN 11
#define ACTUAL_MAX_ROLE_LEN 16

typedef struct {
    char name[ACTUAL_MAX_NAME_LEN];
    char role[ACTUAL_MAX_ROLE_LEN];
    char dateOfBirth[ACTUAL_MAX_DATE_LEN];
    long salary;
} chefObj;

/* ... */

const char* ROLES_TABLE[] = {
    "APPRENTICE COOK",
    "JUNIOR CHEF",
    "SEASONED CHEF",
    "MASTER CHEF"
};
const int ROLES_TABLE_LEN = sizeof(ROLES_TABLE) / sizeof(ROLES_TABLE[0]);
```

### 1.2 Cách thức tương tác

Chương trình không tương tác trực tiếp với cấu trúc `struct chefObj` mà phải thông qua những hàm sau:

``` c
#define MAX_NAME_LEN 30
#define SET_PROPERTY_FAIL 0
#define SET_PROPERTY_OKAY 1

int setName(chefObj* chefPtr, char* namePtr);
int setRole(chefObj* chefPtr, char* rolePtr);
int setSalary(chefObj* chefPtr, long salary);
int setDateOfBirth(chefObj* chefPtr, char* dateOfBirth);

char* getName(chefObj* chef);
char* getRole(chefObj* chef);
char* getDateOfBirth(chefObj* chef);
long getSalary(chefObj* chef);
```

Điều này là để đơn giản hóa quá trình sử dụng truy cập và chỉnh sửa thông tin của từng đầu bếp một, bởi vì ta có thể tích hợp sẵn chức năng kiểm tra dữ liệu đầu vào và đầu ra vào hàm như sau:

``` c
/* ... */

int setName(chefObj* chefPtr, char* namePtr) {
    if (chefPtr == NULL || namePtr == NULL) { return SET_PROPERTY_FAIL; }

    if (isInvalidString(namePtr, MAX_NAME_LEN)) { return SET_PROPERTY_FAIL; }

    formatName(namePtr);
    strncpy(chefPtr->name, namePtr, ACTUAL_MAX_NAME_LEN);

    return SET_PROPERTY_OKAY;
}

char* getName(chefObj* chef) {
    if (chef == NULL) { return NULL; }

    char* name = chef->name;
    return name;
}

/* ... */
```

## 2. Cấu trúc danh sách đầu bếp

Một danh sách đầu bếp về bản chất là một _mảng chứa toàn con trỏ tới `struct`_. So với cấu trúc mảng `struct` thông thường thì cấu trúc này có phần phức tạp hơn (_có lẽ là một cách không cần thiết_). Tuy nhiên, xét về tính linh hoạt và tiết kiệm bộ nhớ thì cấu trúc mảng chứa toàn con trỏ tới `struct` sẽ có ưu thế hơn. Điều này lại càng đúng khi ta muốn truyền một `struct` làm tham số cho một hàm. Để tránh tình trạng sao chép dữ liệu một cách không cần thiết thì ta phải truyền con trỏ `struct` vào hàm đó.

``` c
#define MAX_CHEFS 250
#define DEFAULT_CHEFLIST_SIZE 10

/* ... */

chefObj ** newChefList(int listLen) {
    if (listLen <= 0 || listLen > MAX_CHEFS) { return NULL; }

    int pointerSize = sizeof(chefObj*);
    chefObj** chefList = calloc(listLen, pointerSize);
    if (chefList == NULL) { return NULL; }

    return chefList;
}

chefObj* newChef(void) {
    chefObj* newChef = calloc(1, sizeof(chefObj));
    if (newChef == NULL) { return NULL; }

    return newChef;
}
```

## 3. Định dạng file lưu trữ

Để tránh hiểu nhầm thì file sử dụng bởi chương trình nên được đặt tên có đuôi là `.chefs`. Tuy nhiên, chương trình có khả năng đọc mọi loại file, miễn là định dạng file hợp lệ.

Mỗi dòng trong file sẽ tượng trưng cho hồ sơ của một đầu bếp, hay cụ thể hơn sẽ là một `struct chefObj` và có định dạng như sau:

```
NAME:Chef Name,ROLE:CHEF ROLE,DOB:YYYY-MM-DD,SAL:1234567890\n
```

Ví dụ:

```
NAME:Nha Lu Hanh,ROLE:MASTER CHEF,DOB:1900-01-01,SAL:98765432\n
```

Mỗi dòng trong file, kể cả dòng cuối, bắt buộc phải có dấu xuống dòng ở cuối nếu không quá trình lưu và đọc file sẽ dễ bị lỗi.

```
1: NAME:Nha Lu Hanh,ROLE:MASTER CHEF,DOB:1900-01-01,SAL:98765432
2: NAME:Gordon Ramsey,ROLE:MASTER CHEF,DOB:1966-11-08,SAL:12345678
3:
```

### 3.1 Cách thức đọc file

Chương trình sẽ đọc file theo từng dòng một. Nghĩa là, chương trình sẽ đọc file cho tới ký tự `\n` rồi sẽ dừng lại để phân tích dòng vừa được đọc.

``` c
/* ... */

    int chefCount = 0;
    while (fgets(line, MAX_LINE_LEN, file) != NULL) {
        if (chefCount > MAX_CHEFS) { break; }

        int isEmptyLine = line[0] == '\n';
        if (isEmptyLine) { continue; }

        chefObj* parsedChef = parseChefLine(line);
        if (parsedChef == NULL) { continue; }

        chefList[chefCount] = parsedChef;
        chefCount++;
    }
    fclose(file);

/* ... */
```

Trong quá trình đọc từng dòng chương trình sẽ tách dòng đó ra thành nhiều phần khác nhau, mỗi phần sẽ tượng trưng cho một thuộc tính nào đó trong `struct chefObj`:

```
/* Dữ liệu gốc */

NAME:Nha Lu Hanh,ROLE:MASTER CHEF,DOB:1900-01-01,SAL:98765432\n

/* Dữ liệu được phân tích */

[0] NAME:Nha Lu Hanh
[1] ROLE:MASTER CHEF
[2] DOB:1900-01-01
[3] SAL:98765432
```

Code cụ thể:

``` c
#define PROPERTY_SEPARATOR ","

/* ... */

    property = strtok_r(line, PROPERTY_SEPARATOR, &propertySavePtr);

    while (property != NULL) {
        int propertyLen = strlen(property);
        if (property[propertyLen - 1] == '\n') {
            property[propertyLen - 1] = '\0';
        }

        int parsingResult = parseChefProperty(property, chefPtr);
        if (parsingResult == SET_PROPERTY_FAIL) {
            free(chefPtr);
            return NULL;
        }

        property = strtok_r(NULL, PROPERTY_SEPARATOR, &propertySavePtr);
    }

/* ... */
```

Tiếp đến ta sẽ phân tích những dữ liệu trên để xác định xem đâu là phần định danh thuộc tính và đâu là giá tri của thuộc tính đó:

```
/* Dữ liệu phân tích lần 1 */

[0] NAME:Nha Lu Hanh
[1] ROLE:MASTER CHEF
[2] DOB:1900-01-01
[3] SAL:98765432

/* Dữ liệu phân tích lần 2 */

[0] NAME - [1] Nha Lu Hanh
[0] ROLE - [1] MASTER CHEF
[0] DOB  - [1] 1900-01-01
[0] SAL  - [1] 98765432
```

Code cụ thể:

``` c
#define IDENTIFIER_SEPARATOR ":"

/* ... */

    char* identifierSavePtr;
    char* identifier = strtok_r(
        property, IDENTIFIER_SEPARATOR, &identifierSavePtr
    );

    char identifierFlag = 0;
    while (identifier != NULL) {

        if (identifierFlag == 0) {
            identifierFlag = determineIdentifier(identifier);
            identifier = strtok_r(
                NULL, IDENTIFIER_SEPARATOR, &identifierSavePtr
            );
            continue;
        }
        int result = interpretIdentifierFlag(chefPtr, identifier, identifierFlag);
        if (result == SET_PROPERTY_FAIL) { return SET_PROPERTY_FAIL; }

        identifierFlag = 0;
    }

/* ... */
```

### 3.2 Cách thức viết file

Cách thức viết file khá là đơn giản: ta chỉ cần in thông tin của từng đầu bếp trong danh sách theo từng dòng một.

``` c
/* ... */

    int i;
    for (i = 0; i < listLen; i++) {
        chefObj* chef = chefList[i];
        if (chef == NULL) { continue; }

        char* name = getName(chef);
        char* role = getRole(chef);
        char* dob = getDateOfBirth(chef);
        long sal = getSalary(chef);

        fprintf(
            file,
            "NAME:%s,ROLE:%s,DOB:%s,SAL:%ld\n",
            name, role, dob, sal
        );
    }

/* ... */
```

## 4. Hiển thị danh sách đầu bếp

Việc in danh sách đầu bếp ra màn hình khá là đơn giản, ta chỉ cần sử dụng một vòng lặp và hiển thị thông tin của từng đầu bếp một trong danh sách thôi. Tuy nhiên, việc trình bày thông tin sao cho đẹp mắt lại là một chuyện khác hoàn toàn.

### 4.1 Trình bày dạng bảng

Để làm cho giao diện danh sách nhìn đẹp hơn, ta có thể trình bày thông tin theo dạng bảng. Ta cũng phải chú ý làm sao cho mọi thông tin đều được xếp ngay ngắn và thẳng hàng.

Ví dụ:

```
/* giao diện xấu */

NO | NAME | D.O.B | SALARY
--------------------------
1 | Gordon Ramsey | 1966-11-08 | 1236789
10 | Guy Fieri | 1968-01-22 | 987654321
100 | Michael Caines | 1969-01-03 | 1357913

/* giao diện nhìn đẹp hơn */

NO  | NAME           | D.O.B      | SALARY
---------------------------------------------
001 | Gordon Ramsey  | 1966-11-08 |   1236789
010 | Guy Fieri      | 1968-01-22 | 987654321
100 | Michael Caines | 1969-01-03 |     13579
```

Trước hết, ta phải tìm được chiều dài của những xâu thông tin dài nhất trong danh sách. Ví dụ với danh sách ở trên, ta sẽ phân tích được như sau:

```
Cột "NO"     : dài nhất là 100, chiều dài 3
Cột "NAME"   : dài nhất là Michael Caines, chiều dài 14
Cột "D.O.B"  : chiều dài luôn luôn là 10
Cột "SALARY" : dài nhất là 987654321, chiều dài 9
```

Ta có thể thực hiện điều trên theo cách sau:

``` c
/* ... */

    short int maxName = 0;
    short int maxRole = 0;
    short int maxSal = 0;
    short int maxPos = 0;

    int i;
    for (i = 0; i < listLen; i++) {
        if (chefList[i] == NULL) { continue; }

        char* name = getName(chefList[i]);
        char* role = getRole(chefList[i]);
        long sal = getSalary(chefList[i]);

        short int nameLen = strlen(name);
        short int roleLen = strlen(role);
        short int salLen = getNumLen(sal);
        short int posLen = getNumLen(i + 1);

        maxName = (nameLen > maxName) ? nameLen : maxName;
        maxRole = (roleLen > maxRole) ? roleLen : maxRole;
        maxSal = (salLen > maxSal) ? salLen : maxSal;
        maxPos = (posLen > maxPos) ? posLen : maxPos;
    }

/* ... */
```

Sau đó, ta sẽ dùng những giá trị chiều dài lớn nhất này để làm khoảng cách _padding_ cho từng cột trong bảng. Ta có thể trực tiếp thêm _padding_ vào trong xâu như sau:

```
"Gordon Ramsey"  -> "Gordon Ramsey "
"Guy Fieri"      -> "Guy Fieri     "
"Michael Caines" -> "Michael Caines"
```

Hoặc ta cũng có thể sử dụng cú pháp _format string_ trong hàm `printf()` cho tiện:

``` c
printf(
    "%0*d | %-*s | %-*s | %*s | %*ld\n",
    maxPosLen, pos,
    maxNameLen, name,
    maxRoleLen, role,
    maxDobLen, dob,
    maxSalLen, sal
);
```

Trong đó dấu sao `*` trong `%*s` chỉ giá trị _padding_ tối đa cho biến này. Code cụ thể trong chương trình sẽ như sau:

``` c
/* ... */

    maxNameLen = maxLens->maxNameLen;
    maxRoleLen = maxLens->maxRoleLen;
    maxSalLen = maxLens->maxSalLen;
    maxDobLen = maxLens->maxDobLen;
    maxPosLen = maxLens->maxPosLen;

    short int maxLineLen = getMaxLineLen(maxLens);

    printTableHeader(maxLens);
    printHorizontalDivider("-", maxLineLen);

    int i;
    for (i = 0; i < listLen; i++) {
        if (chefList[i] == NULL) { continue; }

        char* name = getName(chefList[i]);
        char* role = getRole(chefList[i]);
        char* dob = getDateOfBirth(chefList[i]);
        long sal = getSalary(chefList[i]);
        int pos = i + 1;

        printf(
            "%0*d | %-*s | %-*s | %*s | %*ld\n",
            maxPosLen, pos,
            maxNameLen, name,
            maxRoleLen, role,
            maxDobLen, dob,
            maxSalLen, sal
        );

/* ... */
```

### 4.2 Sắp xếp danh sách

Đôi khi người dùng sẽ muốn hiển thị danh sách đầu bếp theo một thứ tự nhất định nào đó, ví dụ như sắp xếp theo bảng chữ cái hoặc là sắp xếp theo lương, vv. Chương trình hỗ trợ hai cách sắp xếp sau: sắp xếp tên theo thứ tự bảng chữ cái A -> Z và sắp xếp theo mức lương theo thứ tự giảm dần.

#### 4.2.1 Sắp xếp theo tên

Để sắp xếp đầu bếp theo tên thì ta sẽ sử dụng thuật toán _selection sort_ và so sánh tên của các đầu bếp với nhau sử dụng hàm `strncmp()`.

Ngoài ra, ta sẽ không trực tiếp sắp xếp danh sách đầu bếp mà trả lại một bản sao đã được sắp xếp. Điều này sẽ giảm thiểu rủi ro làm hư hỏng dữ liệu gốc một cách bất cập.

``` c
/* ... */

void swapChef(chefObj ** firstChef, chefObj ** secondChef) {
    chefObj* temp = *firstChef;
    *firstChef = *secondChef;
    *secondChef = temp;
}

chefObj ** orderByName(chefObj ** chefList, int listLen) {
    if (chefList == NULL || listLen <= 0) { return NULL; }

    chefObj ** sortedList = copyChefList(chefList, listLen);
    if (sortedList == NULL) { return NULL; }

    // Selection sort.
    int i, j;
    for (i = 0; i < listLen; i++) {
        if (sortedList[i] == NULL) { continue; }
        int minIndex = i;

        for (j = i + 1; j < listLen; j++) {
            if (sortedList[j] == NULL) { continue; }

            char* comparedName = getName(sortedList[minIndex]);
            char* currentName = getName(sortedList[j]);

            int isNotAlphabeticallySmaller = (
                strncmp(currentName, comparedName, MAX_NAME_LEN) >= 0
            );
            if (isNotAlphabeticallySmaller) { continue; }

            minIndex = j;
        }
        swapChef(&sortedList[minIndex], &sortedList[i]);
    }

    return sortedList;
}

/* ... */
```

#### 4.2.2 Sắp xếp theo lương

Tương tự như phần sắp xếp theo tên, ta cũng sẽ sao chép danh sách gốc và sử dụng thuật toán _selection sort_ cho phần sắp xếp.

``` c
/* ... */

        for (j = i + 1; j < listLen; j++) {
            if (sortedList[j] == NULL) { continue; }

            long comparedSalary = getSalary(sortedList[maxIndex]);
            long currentSalary = getSalary(sortedList[j]);

            if (currentSalary <= comparedSalary) { continue; }
            maxIndex = j;
        }
        swapChef(&sortedList[maxIndex], &sortedList[i]);

/* ... */
```

## 5. Tìm kiếm thông tin

Nhìn chung, chương trình hỗ trợ tìm kiếm đầu bếp theo tên hoặc là theo mức lương. Bởi vì chương trình không tự động lưu bản sao đã được sắp xếp sẵn của danh sách đầu bếp, ta sẽ sử dụng thuật toán _tìm kiếm tuần tự_ cho đơn giản.

### 5.1 Tìm kiếm theo tên

Để tăng tỉ lệ tìm kiếm thành công, ta sẽ chuyển đổi từ khóa tìm kiếm và tên của đầu bếp hiện tại trong danh sách sang dạng chữ cái in thường. Ngoài ra, thay vì sử dụng hàm `strncmp()` thì ta sẽ sử dụng hàm `strstr()` để trả lại kết quả bao quát hơn:

Ví dụ:

```
NO | NAME                         | D.O.B      | SALARY
----------------------------------------------------------
01 | Marcus                       | 1900-01-01 | 123456789
02 | Marcus Aurelius Antoninus    | 1900-01-01 | 987654321
03 | Marcus Ulpius Nerva Traianus | 1900-01-01 | 112233445

/* strncmp() */

Từ khóa "marcus" -> 1 kết quả

/* strstr() */

Từ khóa "marcus" -> 3 kết quả
```

Code cụ thể sẽ như sau:

``` c
/* ... */

    lowerStr(nameQuery, strlen(nameQuery));

    int matches = 0;
    int i;
    for (i = 0; i < listLen; i++) {
        if (chefList[i] == NULL) { continue; }

        char currentName[ACTUAL_MAX_NAME_LEN];
        strncpy(currentName, getName(chefList[i]), ACTUAL_MAX_NAME_LEN);
        lowerStr(currentName, strlen(currentName));

        char* matchNameResult = strstr(currentName, nameQuery);
        if (matchNameResult == NULL) { continue; }

        insertChefIntoList(matchList, listLen, chefList[i]);
        matches++;
    }

/* ... */
```

### 5.2 Tìm kiếm theo mức lương

So với việc tìm kiếm theo tên, tìm kiếm theo mức lương sẽ đơn giản hơn: ta chỉ cần kiểm tra xem lương của đầu bếp có nằm trong khoảng tìm kiếm hay không.

``` c
/* ... */

    int matches = 0;
    int i;
    for (i = 0; i < listLen; i++) {
        if (chefList[i] == NULL) { continue; }

        long currentSalary = getSalary(chefList[i]);

        int isMatchingSalary = currentSalary >= minSalary && currentSalary <= maxSalary;
        if (isMatchingSalary == 0) { continue; }

        insertChefIntoList(matchList, listLen, chefList[i]);
        matches++;
    }

/* ... */
```

## 6. Thiết kế giao diện

Để cho trải nghiệm người dùng được "_mượt mà_" nhất có thể, việc thiết kế giao diện có những tiêu chí sau:

* **Tính rõ ràng:** người dùng luôn biết được mình có thể thực hiện được những thao tác gì và kết quả của thao tác mình vừa thực hiện. Nói cách khác, người dùng không bị bối rối về việc _mình phải làm gì_.

* **Tính thẩm mỹ:** thông tin được trình bày một cách gọn gàng và các loại thông tin khác nhau phải được phân biệt một cách rõ ràng. Ngoài ra, ta sẽ không hiển thị quá nhiều thông tin trừ khi người dùng yêu cầu vậy.

* **Tính linh hoạt:** người dùng có thể tự do di chuyển từ menu này sang menu khác tùy theo ý muốn (_tùy thuộc vào hoàn cảnh_)

