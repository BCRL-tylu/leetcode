class Solution 
{
public:
    bool phonePrefix(const vector<string>& numbers) const 
    {

        assert(numbers.size() >= MIN_PHONE_COUNT && numbers.size() <= MAX_PHONE_COUNT);

        const size_t totalNumbers = numbers.size();

        for (size_t i = 0; i < totalNumbers; ++i)
        {
            const string& currentPhone = numbers[i];
            const size_t currentLength = currentPhone.size();
            assert(currentLength >= MIN_PHONE_LENGTH && currentLength <= MAX_PHONE_LENGTH);
            for (size_t j = 0; j < totalNumbers; ++j)
            {
                if (i == j) continue;
                const string& otherPhone = numbers[j];
                const size_t otherLength = otherPhone.size();
                if (currentLength <= otherLength)
                {
                    bool bIsPrefix = true;
                    for (size_t k = 0; k < currentLength; ++k)
                    {
                        assert(isdigit(currentPhone[k]));
                        assert(isdigit(otherPhone[k]));
                        if (currentPhone[k] != otherPhone[k])
                        {
                            bIsPrefix = false;
                            break;
                        }
                    }
                    if (bIsPrefix == true)
                    {
                        return false;
                    }
                }
            }
        }

        return true;
    }

private:
    enum
    {
        MIN_PHONE_COUNT = 2,
        MAX_PHONE_COUNT = 50,
        MIN_PHONE_LENGTH = 1,
        MAX_PHONE_LENGTH = 50
    };
};


/*

---

**3491. 전화번호 접두사**

**난이도:** 쉬움

**문제 설명:**  
문자열 배열 **numbers**가 주어지며, 이 배열은 전화번호들을 나타냅니다.  
어떤 전화번호가 다른 전화번호의 접두사(prefix)인 경우가 없다면 true를 반환하고, 그렇지 않다면 false를 반환하세요.

---

**예제 1:**

- **입력:** numbers = ["1","2","4","3"]
- **출력:** true
- **설명:**  
  어떤 번호도 다른 번호의 접두사가 아니므로 결과는 true입니다.

---

**예제 2:**

- **입력:** numbers = ["001","007","15","00153"]
- **출력:** false
- **설명:**  
  문자열 "001"은 문자열 "00153"의 접두사이므로, 결과는 false입니다.

---

**제약 조건:**

- 2 <= numbers.length <= 50  
- 1 <= numbers[i].length <= 50  
- 모든 전화번호는 숫자 '0'부터 '9'로만 구성됩니다.

---

**힌트:**

1. 배열을 정렬하세요.
2. 인접한 두 요소에 대해, 왼쪽 번호가 오른쪽 번호의 접두사인지 확인하세요.

---

이와 같이 문제를 해결하면 됩니다.
*/