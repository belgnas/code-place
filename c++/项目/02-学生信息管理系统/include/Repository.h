// Repository.h — 通用数据仓库模板
// 模板 + 泛型编程的应用：一套代码管理任意类型的数据
// 使用 vector 存储，unique_ptr 管理生命周期

#pragma once
#include<vector>
#include<memory>
#include<algorithm>
#include<string>
#include<stdexcept>

template<typename T>
class Repository
{
public:
    Repository() = default;

    // ---- 增删改查 ----

    // 添加记录（接管所有权）
    void add(std::unique_ptr<T> item)
    {
        m_Items.push_back(std::move(item));
    }

    // 按 ID 删除（返回是否成功）
    bool removeById(const std::string& id)
    {
        auto it = std::find_if(m_Items.begin(), m_Items.end(),
            [&id](const auto& ptr) { return ptr->getId() == id; });

        if (it != m_Items.end())
        {
            m_Items.erase(it);           // unique_ptr 自动析构
            return true;
        }
        return false;
    }

    // 按 ID 查找（返回裸指针，不转移所有权）
    T* findById(const std::string& id) const
    {
        auto it = std::find_if(m_Items.begin(), m_Items.end(),
            [&id](const auto& ptr) { return ptr->getId() == id; });

        return (it != m_Items.end()) ? it->get() : nullptr;
    }

    // 按名字模糊查找
    std::vector<T*> findByName(const std::string& name) const
    {
        std::vector<T*> result;
        for (const auto& ptr : m_Items)
        {
            if (ptr->getName().find(name) != std::string::npos)
            {
                result.push_back(ptr.get());
            }
        }
        return result;
    }

    // 获取所有记录（裸指针，只读）
    std::vector<T*> getAll() const
    {
        std::vector<T*> result;
        result.reserve(m_Items.size());
        for (const auto& ptr : m_Items)
        {
            result.push_back(ptr.get());
        }
        return result;
    }

    // 按角色筛选
    std::vector<T*> getByRole(const std::string& role) const
    {
        std::vector<T*> result;
        for (const auto& ptr : m_Items)
        {
            if (ptr->getRole() == role)
            {
                result.push_back(ptr.get());
            }
        }
        return result;
    }

    // 获取总数
    size_t size() const { return m_Items.size(); }
    bool   empty() const { return m_Items.empty(); }

    // 清空
    void clear() { m_Items.clear(); }

    // 移动底层容器的所有权（用于序列化等场景）
    // 调用后此 Repository 为空
    std::vector<std::unique_ptr<T>> releaseAll()
    {
        return std::move(m_Items);
    }

private:
    // 用 vector 存 unique_ptr → 内存自动管理，零泄漏风险
    std::vector<std::unique_ptr<T>> m_Items;
};
