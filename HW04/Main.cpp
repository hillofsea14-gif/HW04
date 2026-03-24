// Main.cpp



#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// PotionRecipe 클래스: 재료 목록을 vector<string>으로 변경
class PotionRecipe
{
public:


    // 생성자: 재료 목록을 받아 초기화하도록 수정
    PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
        : potionName(name), ingredients(ingredients)
    {
    }

    std::string getName() const
    {
        return potionName;
    }

    const std::vector<std::string>& getIngredients() const
    {
        return ingredients;
    }


private:
    std::string potionName;
    std::vector<std::string> ingredients; // 단일 재료에서 재료 '목록'으로 변경
};

// AlchemyWorkshop 클래스: 레시피 목록을 관리
class AlchemyWorkshop
{
private:
    std::vector<PotionRecipe> recipes;

public:
    // addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients)
    {
        recipes.push_back(PotionRecipe(name, ingredients));
        std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다." << std::endl;
    }

    // 모든 레시피 출력 메서드
    void displayAllRecipes() const
    {
        if (recipes.empty())
        {
            std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
            return;
        }

        std::cout << "\n--- [ 전체 레시피 목록 ] ---" << std::endl;
        for (size_t i = 0; i < recipes.size(); ++i)
        {
            std::cout << "- 물약 이름: " << recipes[i].getName() << std::endl;
            std::cout << "  > 필요 재료: ";

            // 재료 목록을 순회하며 출력
            for (size_t j = 0; j < recipes[i].getIngredients().size(); ++j)
            {
                std::cout << recipes[i].getIngredients()[j];
                // 마지막 재료가 아니면 쉼표로 구분
                if (j < recipes[i].getIngredients().size() - 1)
                {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "---------------------------\n";
    }

    void searchRecipeByName()
    {
        if (recipes.empty())   // recipes가 비었는지 확인.
        {
            std::cout << "아직 등록된 레시피가 없습니다.\n\n" << std::endl;
            return;
        }

        while (true)
        {
            std::string target;
            std::cout << "찾고 싶은 물약의 이름을 적어주세요." << std::endl;
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, target);

            auto it = std::find_if(recipes.begin(), recipes.end(), [&](const PotionRecipe& r)   // 반복자로 받기.
                {
                    return r.getName() == target;
                });

            if (it != recipes.end())
            {
                //size_t PNameIndex = it - recipes.begin(); 반복자는 해당 위치를 가리키기때문에 그냥 반복자를 쓰면됨.
                std::cout << it->getName() << "의 레시피가 존재합니다." << std::endl;
                std::cout << it->getName() << "의 재료는 다음과 같습니다." << std::endl;
                std::cout << "재료 : ";

                for (int i = 0; i < it->getIngredients().size(); ++i)
                {
                    std::cout << it->getIngredients()[i];

                    if (i < it->getIngredients().size() - 1)
                    {
                        std::cout << " , ";
                    }
                }
                std::cout << "\n\n" << std::endl;     // 분리해서 보기 편하게 개행을 두 번함.

                break;
            }
            else
            {
                std::cout << "입력한 이름의 물약은 등록되지 않았습니다.\n\n";
            }

        }
        return;
    }


    void searchRecipesByIngredient() const
    {
        if (recipes.empty())   // recipes가 비었는지 확인.
        {
            std::cout << "아직 등록된 레시피가 없습니다.\n\n" << std::endl;
            return;
        }

        bool found = false;
        std::string targetIngredient;

        std::cout << "재료명을 입력해주세요." << std::endl;
        std::cin.ignore(10000, '\n');
        std::getline(std::cin, targetIngredient);

        std::cout << "\n['" << targetIngredient << "']이(가) 포함된 레시피" << std::endl;

        for (const auto& recipe : recipes)
        {
            // getter 사용해 각 레시피의 재료 목록을 얻어옴.
            const auto& igs = recipe.getIngredients();

            // 그 목록 안에 targetIngredient가 있는지 확인.
            if (std::find(igs.begin(), igs.end(), targetIngredient) != igs.end())
            {
                std::cout << "- " << recipe.getName() << std::endl;
                found = true;
            }
        }

        if (!found)
        {
            std::cout << "해당 재료를 사용하는 레시피가 없습니다." << std::endl;
        }
        std::cout << "\n\n";
    }
};

int main()
{
    AlchemyWorkshop myWorkshop;

    while (true)
    {
        std::cout << "연금술 공방 관리 시스템" << std::endl;
        std::cout << "1. 레시피 추가" << std::endl;
        std::cout << "2. 모든 레시피 출력" << std::endl;
        std::cout << "3. 물약 이름으로 레시피 찾기" << std::endl;
        std::cout << "4. 재료 이름으로 재료가 포함된 레시피 찾기" << std::endl;
        std::cout << "5. 종료" << std::endl;
        std::cout << "선택: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cout << "잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1)
        {
            std::string name;
            std::cout << "물약 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);

            // 여러 재료를 입력받기 위한 로직
            std::vector<std::string> ingredients_input;
            std::string ingredient;
            std::cout << "필요한 재료들을 입력하세요. (입력 완료 시 '끝' 입력)" << std::endl;

            while (true)
            {
                std::cout << "재료 입력: ";
                std::getline(std::cin, ingredient);

                // 사용자가 '끝'을 입력하면 재료 입력 종료
                if (ingredient == "끝")
                {
                    break;
                }
                ingredients_input.push_back(ingredient);
            }

            // 입력받은 재료가 하나 이상 있을 때만 레시피 추가
            if (!ingredients_input.empty())
            {
                myWorkshop.addRecipe(name, ingredients_input);
            }
            else
            {
                std::cout << ">> 재료가 입력되지 않아 레시피 추가를 취소합니다." << std::endl;
            }

        }
        else if (choice == 2)
        {
            myWorkshop.displayAllRecipes();

        }
        else if (choice == 3)
        {
            myWorkshop.searchRecipeByName();
        }
        else if (choice == 4)
        {
            myWorkshop.searchRecipesByIngredient();
        }
        else if (choice == 5)
        {
            std::cout << "공방 문을 닫습니다..." << std::endl;
            break;

        }
        else
        {
            std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
        }
    }

    return 0;
}