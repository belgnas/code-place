# Git 使用教程

> **文档说明**：本文是 Git 版本控制工具的系统性教程，从基础概念到日常使用、从分支管理到团队协作，逐项讲解每种操作的用途、命令、示例和注意事项。
> 如果你只需要快速完成日常推送，可以先看 [日常推送.md](日常推送.md)；想系统掌握 Git，建议通读本教程。

---

## 📑 目录

- [1. 什么是 Git](#1-什么是-git)
- [2. 安装与配置](#2-安装与配置)
- [3. Git 核心概念](#3-git-核心概念)
- [4. 基础操作](#4-基础操作)
- [5. 分支管理](#5-分支管理)
- [6. 远程仓库](#6-远程仓库)
- [7. 撤销与回退](#7-撤销与回退)
- [8. 暂存与贮藏（stash）](#8-暂存与贮藏stash)
- [9. 标签管理（tag）](#9-标签管理tag)
- [10. 变基（rebase）](#10-变基rebase)
- [11. 拣选提交（cherry-pick）](#11-拣选提交cherry-pick)
- [12. .gitignore 文件](#12-gitignore-文件)
- [13. 协作工作流](#13-协作工作流)
- [14. 日志与追溯](#14-日志与追溯)
- [15. 常见场景速查](#15-常见场景速查)
- [16. 最佳实践与习惯](#16-最佳实践与习惯)
- [17. Git 托管平台差异](#17-git-托管平台差异)

---

## 1. 什么是 Git

Git 是一个**分布式版本控制系统**，由 Linus Torvalds 于 2005 年创建（同时也是 Linux 内核的创建者）。它用于追踪文件的变更历史，支持多人协作，是现代软件开发中最基本的工具之一。

### 核心特点

| 特点 | 说明 |
| --- | --- |
| 分布式 | 每个人本地都有完整的仓库副本，不依赖中央服务器 |
| 快照存储 | Git 记录的是文件的完整快照（snapshot），而非文件差异 |
| 分支轻量 | 创建分支几乎瞬间完成，鼓励频繁使用分支 |
| 本地操作 | 绝大多数操作在本地完成，速度快，离线可用 |
| 数据完整性 | 所有内容通过 SHA-1 哈希校验，确保数据不被篡改 |
| 暂存区 | 提供"暂存区"机制，精细控制每次提交的内容 |

### Git 能做什么

- 记录代码的每一次修改历史
- 回到过去的任意版本
- 并行开发多个功能（分支）
- 多人协作合并代码
- 追踪每一行代码是谁、什么时候改的

### 哪些人在用 Git

- 软件开发者（几乎所有公司）
- 算法竞赛选手（备份代码、记录题解）
- 学生（管理课程作业、笔记和项目）
- 写作者（写技术博客、书籍）

---

## 2. 安装与配置

### 2.1 安装 Git

**Windows**
- 从 [git-scm.com](https://git-scm.com/) 下载安装包，一路默认安装即可
- 安装时会附带 **Git Bash**（类 Unix 终端），建议保留

安装完成后，终端输入以下命令验证：

```bash
git --version
# 输出示例：git version 2.45.0.windows.1
```

**macOS**
```bash
# 方式一：Xcode Command Line Tools 自带
xcode-select --install

# 方式二：Homebrew
brew install git
```

**Linux (Ubuntu/Debian)**
```bash
sudo apt update
sudo apt install git
```

### 2.2 基本配置

安装后首先要配置用户名和邮箱，这些信息会记录到每一次提交中：

```bash
git config --global user.name "你的名字"
git config --global user.email "你的邮箱@example.com"
```

> `--global` 表示全局配置，对本机的所有仓库生效。去掉 `--global` 则只对当前仓库生效。

### 2.3 查看配置

```bash
# 查看所有配置
git config --list

# 查看某项配置
git config user.name
git config user.email
```

### 2.4 常用可选配置

```bash
# 设置默认分支名为 main（GitHub 已默认）
git config --global init.defaultBranch main

# 解决 Windows 换行符问题（CRLF ↔ LF）
git config --global core.autocrlf true      # Windows
git config --global core.autocrlf input     # macOS / Linux

# 配置默认编辑器（提交信息时使用）
git config --global core.editor "code --wait"    # VS Code
git config --global core.editor vim              # Vim

# 设置命令别名（简化常用命令）
git config --global alias.st status
git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.ci commit
git config --global alias.lg "log --oneline --graph --all"
```

> 设置别名后，`git st` 等价于 `git status`，`git lg` 等价于漂亮的日志输出。

### 2.5 配置文件的位置

| 级别 | 文件路径 | 作用范围 |
| --- | --- | --- |
| 系统级 | `C:\ProgramData\Git\config`（Windows）或 `/etc/gitconfig` | 本机所有用户 |
| 全局级 | `~/.gitconfig` 或 `C:\Users\用户名\.gitconfig` | 当前用户的所有仓库 |
| 仓库级 | `.git/config`（仓库目录内） | 仅当前仓库 |

> 优先级：**仓库级 > 全局级 > 系统级**

---

## 3. Git 核心概念

在使用 Git 之前，理解下面几个概念非常重要。

### 3.1 三个区域

```
工作目录（Working Directory）
    │  git add
    ▼
暂存区（Staging Area / Index）
    │  git commit
    ▼
本地仓库（Local Repository / .git）
    │  git push
    ▼
远程仓库（Remote Repository / GitHub 等）
```

| 区域 | 说明 | 对应操作 |
| --- | --- | --- |
| **工作目录** | 你电脑上的实际文件，正在编辑的内容 | 写代码、改文件 |
| **暂存区** | 准备提交的文件清单，介于工作目录和仓库之间 | `git add` |
| **本地仓库** | `.git` 目录，存储所有历史版本 | `git commit` |
| **远程仓库** | 托管在 GitHub / GitLab 等平台上的仓库 | `git push` / `git pull` |

### 3.2 文件状态

一个文件在 Git 中可能处于以下几种状态：

```
未跟踪（Untracked）──git add──▶ 已暂存（Staged）──git commit──▶ 已提交（Committed）
                                     ▲                        │
                                     └──── git add ───────────┘
                                    （修改后重新暂存）
```

| 状态 | 含义 | `git status` 显示 |
| --- | --- | --- |
| Untracked | 新文件，Git 尚未追踪 | 红色，`Untracked files` |
| Modified | 已追踪的文件被修改，但未暂存 | 红色，`Changes not staged for commit` |
| Staged | 修改已添加到暂存区，等待提交 | 绿色，`Changes to be committed` |
| Committed | 已提交到本地仓库 | 不显示（`nothing to commit`） |

### 3.3 提交（Commit）

每次 `git commit` 会产生一个**快照**，包含：

- 一个唯一的 SHA-1 哈希值（如 `a1b2c3d...`）
- 作者和提交时间
- 提交信息（commit message）
- 指向父提交的指针（形成历史链条）

```
提交1 ◀── 提交2 ◀── 提交3 ◀── 提交4（HEAD → main）
```

### 3.4 HEAD、分支与指针

- **HEAD**：指向当前所在的分支（或某次提交），可以理解为"我在哪里"
- **分支（branch）**：指向某次提交的轻量级指针，可以独立向前移动
- **标签（tag）**：固定指向某次提交，不会移动（通常用于标记版本号）

```
HEAD → main → commit-4 → commit-3 → commit-2 → commit-1
              ↑
         feature-branch → commit-5（在 commit-4 基础上）
```

---

## 4. 基础操作

### 4.1 初始化仓库

**方式一：在本地新建仓库**

```bash
# 创建项目目录并进入
mkdir my-project
cd my-project

# 初始化 Git 仓库
git init
```

执行后目录下会生成一个 `.git` 隐藏文件夹，这就是仓库的核心。

**方式二：克隆远程已有仓库**

```bash
git clone https://github.com/用户名/仓库名.git

# 克隆到指定目录
git clone https://github.com/用户名/仓库名.git 自定义目录名
```

### 4.2 查看状态

`git status` 是最常用的命令之一，告诉你当前仓库的状态：

```bash
git status

# 简洁输出
git status -s

# 输出解读：
#  ??  → 未追踪的新文件
#  M  → 已修改（红色：未暂存 / 绿色：已暂存）
#  A  → 新添加到暂存区的文件
#  D  → 已删除的文件
```

### 4.3 添加文件到暂存区

```bash
# 添加指定文件
git add 文件名.cpp

# 添加多个文件
git add file1.cpp file2.md

# 添加当前目录所有变更
git add .

# 添加所有变更（包括上层目录）
git add -A

# 交互式选择添加（按块选择）
git add -p
```

### 4.4 提交

```bash
# 提交并附带信息
git commit -m "提交信息"

# 提交所有已追踪的修改（跳过 git add）
git commit -a -m "提交信息"

# 修改最近一次的提交（补充遗漏的文件或修改信息）
git add 遗漏的文件
git commit --amend -m "新的提交信息"

# 只改提交信息，不改内容
git commit --amend -m "修改后的信息"
```

> ⚠️ `--amend` 会**改写历史**，如果已经 push 到远程，不要对已推送的提交使用。

### 4.5 提交信息规范

好的提交信息能让未来的你（和协作者）快速理解每次改动：

```bash
# ✅ 好的提交信息
git commit -m "修复浮点数精度导致的排序错误"
git commit -m "添加高精度加法模板"
git commit -m "2026-07-16 整理git教程 + 更新CF题解"

# ❌ 不好的提交信息
git commit -m "修改"
git commit -m "update"
git commit -m "fix bug"
```

推荐格式（参考你的日常推送风格）：

```bash
git commit -m "日期 事件1 + 事件2 + 事件3"
# 示例
git commit -m "2026-07-16 整理git教程 + 完成两道CF题目 + 更新README"
```

### 4.6 查看提交历史

```bash
# 基本日志
git log

# 单行显示（简洁）
git log --oneline

# 图形化显示分支历史
git log --oneline --graph --all

# 查看最近 N 次提交
git log -3

# 查看某个文件的修改历史
git log 文件名

# 查看每次提交改了什么
git log -p

# 查看某个作者的提交
git log --author="名字"
```

> 提示：如果设置了别名 `git lg`，可以直接用 `git log --oneline --graph --all` 的简洁视图。

### 4.7 查看差异

```bash
# 查看工作区与暂存区的差异（尚未 git add 的内容）
git diff

# 查看暂存区与最新提交的差异（已 git add 但未 commit 的内容）
git diff --staged
# 或
git diff --cached

# 查看工作区与某次提交的差异
git diff HEAD
git diff 提交哈希

# 查看两次提交之间的差异
git diff 提交A 提交B

# 查看某个文件的差异
git diff 文件名

# 只显示文件名列表
git diff --name-only
```

### 4.8 移动和删除文件

```bash
# 移动/重命名文件（Git 会自动追踪）
git mv 旧文件名 新文件名

# 删除文件
git rm 文件名

# 只从 Git 中移除追踪，保留本地文件
git rm --cached 文件名
```

> 直接用系统的文件管理器移动或删除文件也可以，之后用 `git add -A` 会让 Git 自动检测到。

### 4.9 忽略文件（.gitignore）

有些文件不应提交到仓库（编译产物、缓存、密钥等），在仓库根目录创建 `.gitignore` 文件：

```gitignore
# 编译产物
*.exe
*.o
*.out
*.class

# IDE 文件
.vs/
.vscode/
.idea/

# CPH 插件缓存
.cph/

# 系统文件
.DS_Store
Thumbs.db

# 日志
*.log

# 环境变量（含密钥）
.env

# 依赖目录
node_modules/
```

> 更多规则参见 [第 12 节](#12-gitignore-文件)。

---

## 5. 分支管理

分支是 Git 最强大的特性之一。它让你可以在不影响主线的前提下，并行开发新功能、修复 bug 或做实验。

### 5.1 什么是分支

分支本质上是一个**指向某次提交的指针**。创建分支不会复制代码，只是新建了一个指针，因此非常轻量。

```
        feature
         │
         ▼
A ── B ── C ── D（main / HEAD）
```

当你切换到 `feature` 分支并提交后：

```
              E（feature / HEAD）
             /
A ── B ── C ── D（main）
```

### 5.2 查看分支

```bash
# 列出本地分支（当前分支前有 * 标记）
git branch

# 列出所有分支（包括远程）
git branch -a

# 查看每个分支的最后一次提交
git branch -v

# 查看已合并到当前分支的分支
git branch --merged

# 查看未合并的分支
git branch --no-merged
```

### 5.3 创建与切换分支

```bash
# 创建分支
git branch 分支名

# 切换分支
git checkout 分支名
# 新式写法（Git 2.23+）
git switch 分支名

# 创建并切换到新分支（一步完成）
git checkout -b 新分支名
# 或
git switch -c 新分支名

# 基于某个提交创建分支
git checkout -b 新分支名 提交哈希
```

> Git 2.23 引入了 `git switch`（切换分支）和 `git restore`（恢复文件），将原本 `git checkout` 的两类功能分开。新命令语义更清晰，但 `checkout` 仍然完全可用。

### 5.4 删除分支

```bash
# 删除本地分支（已合并）
git branch -d 分支名

# 强制删除本地分支（即使未合并）
git branch -D 分支名

# 删除远程分支
git push origin --delete 分支名
```

### 5.5 合并分支（merge）

将一个分支的修改合并到当前分支：

```bash
# 1. 切换到目标分支（如 main）
git switch main

# 2. 合并其他分支
git merge 要合并的分支名
```

**合并的两种情况：**

- **快进合并（Fast-forward）**：被合并的分支是当前分支的直接后继，Git 只是把指针前移，不会产生新的合并提交。

```
合并前：A ── B ── C（main）── D ── E（feature）
合并后：A ── B ── C ── D ── E（main, feature）
```

- **三方合并（3-way merge）**：两个分支都有各自的提交，Git 会创建一个新的"合并提交"来整合两者。

```
合并前：      D ── E（feature）
             /
      A ── B ── C ── F（main）

合并后：      D ── E ──┐
             /          \
      A ── B ── C ── F ── G（main）  ← G 是合并提交
```

### 5.6 合并冲突

当两个分支修改了**同一个文件的同一部分**时，Git 无法自动决定保留哪个版本，就会产生冲突。

**冲突文件的内容：**

```
<<<<<<< HEAD
当前分支的内容
=======
要合并分支的内容
>>>>>>> feature-branch
```

**解决步骤：**

```bash
# 1. 查看哪些文件有冲突
git status

# 2. 手动编辑冲突文件，保留想要的内容，删除 <<<<<<< ======= >>>>>>> 标记

# 3. 标记冲突已解决
git add 冲突文件

# 4. 完成合并
git commit -m "合并 feature-branch，解决冲突"
```

> **技巧**：VS Code 等编辑器内置了冲突解决工具，可以一键选择"保留当前"、"保留传入"或"保留两者"。

**取消合并**

```bash
# 如果合并过程中想放弃
git merge --abort
```

### 5.7 分支策略

个人项目常用的简单策略：

```bash
# 在 feature 分支上开发，完成后合并到 main
main ──────●─────────●─────────●──────▶
            \         \         \
feature1 ────●──●──●   \         \
                         \         \
                feature2 ──●──●──●──●
```

团队协作常用 **Git Flow** 或 **GitHub Flow**：

| 分支 | 用途 |
| --- | --- |
| `main` / `master` | 稳定发布版本 |
| `develop` | 开发主线 |
| `feature/xxx` | 新功能开发 |
| `hotfix/xxx` | 紧急修复 |
| `release/xxx` | 发布准备 |

---

## 6. 远程仓库

远程仓库是托管在网络上的 Git 仓库，用于备份和协作。常见平台有 GitHub、GitLab、Gitee 等。

### 6.1 查看远程仓库

```bash
# 列出远程仓库
git remote

# 显示详细 URL
git remote -v
```

### 6.2 添加远程仓库

```bash
# 添加远程仓库（origin 是约定的默认名称）
git remote add origin https://github.com/用户名/仓库名.git

# 添加多个远程仓库（如同时推送到 GitHub 和 Gitee）
git remote add github https://github.com/用户名/仓库名.git
git remote add gitee https://gitee.com/用户名/仓库名.git
```

### 6.3 推送（push）

```bash
# 推送到远程仓库
git push origin main

# 首次推送并设置上游分支（之后可以直接 git push）
git push -u origin main

# 推送所有分支
git push --all

# 推送标签
git push --tags

# 强制推送（⚠️ 危险操作，会覆盖远程历史）
git push --force
# 更安全的强制推送（只在远程没有新提交时执行）
git push --force-with-lease
```

> ⚠️ `--force` 会覆盖远程仓库的历史。**永远不要**对共享分支（如 `main`）使用强制推送。

### 6.4 拉取（fetch / pull）

```bash
# 只下载远程更新，不合并（推荐先 fetch）
git fetch origin

# 下载并合并到当前分支
git pull origin main

# 等价于
git fetch origin main
git merge origin/main

# 使用 rebase 而非 merge 来拉取（保持历史线整洁）
git pull --rebase origin main
```

> **`fetch` vs `pull`**：`fetch` 只是下载，不影响本地代码，更安全；`pull` = `fetch` + `merge`，直接修改你的工作目录。建议**先 fetch 查看变化，再决定是否 merge**。

### 6.5 克隆（clone）

```bash
# 克隆远程仓库到本地
git clone https://github.com/用户名/仓库名.git

# 克隆指定分支
git clone -b 分支名 https://github.com/用户名/仓库名.git

# 浅克隆（只取最近一次提交，节省时间和空间）
git clone --depth 1 https://github.com/用户名/仓库名.git
```

### 6.6 关联远程仓库的完整流程

从零开始在 GitHub 上创建仓库并关联本地代码：

```bash
# 1. 在 GitHub 网页上创建新仓库（不要勾选 README、.gitignore 等）

# 2. 本地初始化
cd 你的项目目录
git init
git add .
git commit -m "初始提交"

# 3. 关联远程并推送
git remote add origin https://github.com/用户名/仓库名.git
git branch -M main           # 确保分支名为 main
git push -u origin main
```

---

## 7. 撤销与回退

### 7.1 撤销工作区的修改（未 git add）

```bash
# 丢弃某个文件的修改，恢复到最近一次 commit 的状态
git restore 文件名
# 旧式写法
git checkout -- 文件名

# 丢弃所有修改
git restore .
```

> ⚠️ 这个操作**不可恢复**，修改内容会被永久丢弃。

### 7.2 取消暂存（已 git add，未 commit）

```bash
# 将文件从暂存区移回工作区（修改保留）
git restore --staged 文件名
# 旧式写法
git reset HEAD 文件名

# 取消所有暂存
git restore --staged .
```

### 7.3 修改最近的提交

```bash
# 修改最近一次的提交信息
git commit --amend -m "新的提交信息"

# 将遗漏的文件补入最近一次提交
git add 遗漏的文件
git commit --amend --no-edit   # 不修改提交信息
```

> ⚠️ 已推送到远程的提交，不要使用 `--amend`。

### 7.4 回退到历史版本（reset）

`git reset` 用于将 HEAD 指针移动到指定的提交：

```bash
# 回退模式对比：

# --soft：只移动 HEAD，保留暂存区和工作区
git reset --soft HEAD~1    # 撤销最近一次 commit，修改保留在暂存区

# --mixed（默认）：移动 HEAD + 清空暂存区，保留工作区
git reset HEAD~1           # 撤销 commit 和 add，修改保留在工作区
git reset --mixed HEAD~1

# --hard：移动 HEAD + 清空暂存区 + 丢弃工作区修改（⚠️ 最危险）
git reset --hard HEAD~1    # 完全回到上一次提交的状态
```

| 模式 | HEAD | 暂存区 | 工作区 | 使用场景 |
| --- | --- | --- | --- | --- |
| `--soft` | ✅ 移动 | 保留 | 保留 | 想重新写提交信息或合并多次提交 |
| `--mixed` | ✅ 移动 | 清空 | 保留 | 撤销 add 和 commit，重新整理 |
| `--hard` | ✅ 移动 | 清空 | **丢弃** | 彻底放弃最近的修改 |

> `HEAD~1` 表示"当前提交的上一个提交"，`HEAD~3` 表示往前数 3 个。也可以用具体的提交哈希。

### 7.5 安全回退（revert）

`git revert` 创建一个**新的提交**来"反向"撤销某次提交的修改，不会改变已有历史，是更安全的回退方式：

```bash
# 撤销某次提交（创建一个反向提交）
git revert 提交哈希

# 撤销最近一次提交
git revert HEAD
```

> **reset vs revert**：`reset` 改写历史（适合本地未推送的提交），`revert` 追加历史（适合已推送的提交）。

### 7.6 恢复误删的文件

```bash
# 恢复被删除的文件（从最近一次提交中取回）
git restore 被删的文件名

# 查看某个文件在历史版本中的内容
git show 提交哈希:文件路径
```

---

## 8. 暂存与贮藏（stash）

当你在一个分支上工作到一半，需要切换到另一个分支处理紧急事务，但又不想提交半成品时，`stash` 就派上用场了。

### 8.1 基本用法

```bash
# 暂存当前所有修改（包括已暂存和未暂存）
git stash

# 暂存时附带描述信息（推荐）
git stash push -m "正在写排序算法，临时切换修bug"

# 暂存所有修改（包括未追踪的文件）
git stash -u
# 或
git stash --include-untracked
```

### 8.2 查看贮藏列表

```bash
git stash list

# 输出示例：
# stash@{0}: On main: 正在写排序算法，临时切换修bug
# stash@{1}: On feature: WIP 通讯录系统
```

### 8.3 恢复贮藏

```bash
# 恢复最近一次贮藏（不删除贮藏记录）
git stash apply

# 恢复指定贮藏
git stash apply stash@{1}

# 恢复最近一次贮藏并删除记录（最常用）
git stash pop

# 恢复指定贮藏并删除
git stash pop stash@{1}
```

### 8.4 删除贮藏

```bash
# 删除最近一次贮藏
git stash drop

# 删除指定贮藏
git stash drop stash@{1}

# 清空所有贮藏
git stash clear
```

### 8.5 将贮藏创建为新分支

```bash
git stash branch 新分支名
```

> 这个命令会将贮藏的内容应用到新分支上，如果恢复成功则自动删除该贮藏。

### 8.6 应用场景

| 场景 | 操作 |
| --- | --- |
| 临时切换分支处理紧急 bug | `git stash` → 切换分支 → 修完切回来 → `git stash pop` |
| 拉取远程更新前暂存本地修改 | `git stash` → `git pull` → `git stash pop` |
| 将当前工作转移到新分支 | `git stash` → `git switch -c 新分支` → `git stash pop` |

---

## 9. 标签管理（tag）

标签用于给某个提交打上固定的记号，通常用来标记版本号（如 `v1.0.0`）。

### 9.1 查看标签

```bash
# 列出所有标签
git tag

# 按模式过滤
git tag -l "v1.*"
```

### 9.2 创建标签

```bash
# 轻量标签（只是一个指针）
git tag v1.0.0

# 附注标签（包含作者、日期、说明信息）——推荐
git tag -a v1.0.0 -m "第一个正式版本"

# 给过去的提交打标签
git tag -a v0.9.0 提交哈希 -m "测试版本"
```

> 轻量标签 vs 附注标签：附注标签是完整的 Git 对象，存储在数据库中，包含校验和信息。建议始终使用附注标签。

### 9.3 查看标签详情

```bash
git show v1.0.0
```

### 9.4 推送标签

```bash
# 推送单个标签
git push origin v1.0.0

# 推送所有标签
git push origin --tags

# 推送附注标签时自动包含标签对象
git push --follow-tags
```

### 9.5 删除标签

```bash
# 删除本地标签
git tag -d v1.0.0

# 删除远程标签
git push origin --delete v1.0.0
# 或
git push origin :refs/tags/v1.0.0
```

### 9.6 基于标签创建分支

```bash
git checkout -b 新分支名 v1.0.0
```

---

## 10. 变基（rebase）

`rebase` 会将一个分支的提交"搬移"到另一个分支的最新提交之后，使历史线保持整洁的直线。

### 10.1 rebase vs merge

**merge** 会产生分叉和合并提交：

```
      D ── E（feature）
     /        \
A ── B ── C ── F ── G（main，G 是合并提交）
```

**rebase** 会改写提交历史，使之变为一条直线：

```
# 在 feature 分支上执行
git rebase main

# 结果：feature 的提交被"接"到了 main 的最新提交上
A ── B ── C ── D' ── E'（feature）
```

> `D'` 和 `E'` 是 `D` 和 `E` 的重写版本，提交哈希改变了。

### 10.2 基本用法

```bash
# 1. 切换到 feature 分支
git switch feature

# 2. 将 feature 的提交 rebase 到 main 的最新提交上
git rebase main

# 3. 如果有冲突，解决后继续
git add 冲突文件
git rebase --continue

# 4. 如果想放弃 rebase
git rebase --abort
```

### 10.3 交互式 rebase

`git rebase -i` 是**最有用的 Git 命令之一**，可以对提交历史进行精细操作：

```bash
# 对最近 3 次提交进行交互式整理
git rebase -i HEAD~3
```

执行后会打开编辑器，列出最近 3 次提交：

```
pick a1b2c3d 第一次提交
pick e4f5g6h 第二次提交
pick i7j8k9l 第三次提交
```

可以修改每行前面的命令：

| 命令 | 说明 |
| --- | --- |
| `pick` (p) | 保留该提交（默认） |
| `reword` (r) | 保留提交，但修改提交信息 |
| `edit` (e) | 保留提交，但暂停以修改内容 |
| `squash` (s) | 将该提交合并到上一个提交 |
| `fixup` (f) | 同 squash，但丢弃该提交的信息 |
| `drop` (d) | 删除该提交 |

**最常用的操作**：将多个零碎的提交合并为一个。

```bash
# 将最近 3 次提交压缩为一个
# 编辑器中：
pick a1b2c3d 第一次提交
squash e4f5g6h 第二次提交    # 改为 squash
squash i7j8k9l 第三次提交    # 改为 squash
```

### 10.4 黄金法则

> ⚠️ **永远不要对已推送到远程共享分支的提交进行 rebase。**
>
> rebase 会改写提交哈希，如果你 rebase 了别人已经基于其上开发的分支，会造成严重的混乱。

简而言之：
- 本地未推送的提交：✅ 可以 rebase
- 已推送到远程的提交：❌ 不要 rebase（除非只有你一个人在用这个分支）
- 对远程 `main` 分支：❌ 绝对不要 rebase

### 10.5 使用 `git pull --rebase`

拉取远程更新时，可以用 rebase 代替 merge，保持历史整洁：

```bash
git pull --rebase origin main
```

> 个人项目推荐使用 `git pull --rebase`，避免产生无意义的合并提交。

---

## 11. 拣选提交（cherry-pick）

`cherry-pick` 可以将某次提交"摘取"到当前分支，只选择你需要的那个提交。

### 11.1 基本用法

```bash
# 将某次提交应用到当前分支
git cherry-pick 提交哈希

# 一次摘取多个提交
git cherry-pick 提交A 提交B 提交C

# 摘取连续的提交范围（不包含 A，包含 B）
git cherry-pick 提交A..提交B
```

### 11.2 应用场景

- 把某个 bug 修复从开发分支搬到发布分支
- 只想要另一个分支上的某一个功能，不需要全部合并
- 错误地在错误的分支上做了提交，想搬过来

### 11.3 有冲突时

```bash
# 解决冲突后继续
git add 冲突文件
git cherry-pick --continue

# 放弃
git cherry-pick --abort
```

---

## 12. .gitignore 文件

`.gitignore` 文件放在仓库根目录，告诉 Git 忽略某些不需要追踪的文件。

### 12.1 语法规则

```gitignore
# 注释以 # 开头

# 忽略特定文件
secret.txt

# 忽略某种后缀的所有文件
*.exe
*.o
*.log

# 忽略某个目录（注意尾部斜杠）
output/
build/
.cph/

# 取反（不忽略），! 开头
*.log          # 忽略所有 .log
!important.log # 但不忽略 important.log

# 匹配任意层级目录中的文件
**/temp/

# 只忽略根目录下的文件（前面加 /）
/todo.txt      # 只忽略根目录的 todo.txt，不忽略子目录中的
```

### 12.2 常用模板（适用于 C++ 算法竞赛项目）

```gitignore
# 编译产物
*.exe
*.out
*.o
*.obj
*.class

# Visual Studio
.vs/
*.sdf
*.suo
*.user

# VS Code（根据需要保留或忽略）
# .vscode/

# CPH 插件缓存
.cph/

# 系统文件
.DS_Store
Thumbs.db

# 临时文件
*.tmp
*.swp
*~

# 输出目录
output/
bin/
build/

# 压缩包
*.zip
*.tar.gz
*.rar
```

### 12.3 注意事项

- `.gitignore` 本身应该加入版本控制（提交到仓库）
- 已经被 Git 追踪的文件不会受 `.gitignore` 影响，需要先 `git rm --cached` 移除追踪
- GitHub 提供了各语言和框架的 `.gitignore` 模板：[github/gitignore](https://github.com/github/gitignore)

---

## 13. 协作工作流

### 13.1 Fork + Pull Request 流程（GitHub）

这是开源社区最常用的协作方式：

```
步骤概览：
1. Fork 原仓库 → 你的账号下出现一个副本
2. Clone 你的副本到本地
3. 在本地创建 feature 分支进行修改
4. 推送到你的远程副本
5. 在 GitHub 上发起 Pull Request（PR）
6. 原仓库维护者审核并合并
```

**详细步骤：**

```bash
# 1. 在 GitHub 网页上点击 Fork 按钮

# 2. Clone 你 Fork 的仓库
git clone https://github.com/你的用户名/仓库名.git
cd 仓库名

# 3. 添加上游仓库（方便同步更新）
git remote add upstream https://github.com/原作者/仓库名.git

# 4. 创建功能分支
git checkout -b feature/新功能

# 5. 修改代码，提交
git add .
git commit -m "添加新功能：XXX"

# 6. 推送到你的 Fork
git push origin feature/新功能

# 7. 在 GitHub 网页上发起 Pull Request

# 8. 后续同步上游更新
git fetch upstream
git checkout main
git merge upstream/main
git push origin main
```

### 13.2 单人项目的日常流程

这就是你目前在用的方式（参见 [日常推送.md](日常推送.md)）：

```bash
# 每天开始工作前
git pull origin main

# 写代码、写题解、记笔记...

# 每天结束前
git add .
git commit -m "2026-07-16 整理git教程 + 完成CF #1234题解 + 更新学习笔记"
git push origin main
```

### 13.3 多人协作同一仓库

```bash
# 1. 开始新功能前，拉取最新代码
git pull origin main

# 2. 创建功能分支
git checkout -b feature/xxx

# 3. 在分支上开发，频繁提交
git add .
git commit -m "完成 XXX 功能的第一部分"

# 4. 定期将 main 的更新合并到你的分支（避免合并时冲突过大）
git checkout main
git pull origin main
git checkout feature/xxx
git merge main

# 5. 开发完成后推送分支
git push origin feature/xxx

# 6. 在平台上发起 Pull Request / Merge Request
# 7. 审核通过后合并，然后删除功能分支
git branch -d feature/xxx
```

---

## 14. 日志与追溯

### 14.1 查看某行代码是谁写的（blame）

```bash
# 查看文件每行的最后修改者和时间
git blame 文件名

# 查看指定行范围
git blame -L 10,30 文件名

# 忽略空白修改
git blame -w 文件名
```

### 14.2 搜索提交历史

```bash
# 在提交信息中搜索关键词
git log --grep="关键词"

# 搜索代码变更（某段代码什么时候被添加或删除的）
git log -S "代码片段"          # 精确匹配
git log -G "正则表达式"        # 正则匹配

# 搜索某个函数的所有变更
git log -L :函数名:文件名
```

### 14.3 查看某次提交的内容

```bash
# 查看提交详情（改了哪些文件）
git show 提交哈希

# 只查看提交信息
git show --stat 提交哈希

# 查看提交中的某个文件
git show 提交哈希:文件路径
```

### 14.4 对比两个版本

```bash
# 查看两个分支的差异
git diff main..feature

# 查看哪些提交在 feature 中但不在 main 中
git log main..feature

# 查看哪些提交在 main 中但不在 feature 中
git log feature..main
```

---

## 15. 常见场景速查

本节汇总日常工作学习中经常遇到的场景和对应的解决方案。

### 场景 1：我提交了，但发现漏了文件

```bash
git add 漏掉的文件
git commit --amend --no-edit
```

### 场景 2：我提交了，但提交信息写错了

```bash
git commit --amend -m "正确的提交信息"
```

### 场景 3：我不小心 add 了不该提交的文件

```bash
git restore --staged 文件名   # 从暂存区移除，但保留修改
```

### 场景 4：我改错了文件，想回到修改之前

```bash
git restore 文件名            # 丢弃工作区修改（未 add 的）
git checkout HEAD -- 文件名    # 丢弃所有修改（回到最新提交的状态）
```

### 场景 5：我提交到了错误的分支

```bash
# 假设你本应在 feature 分支提交，却不小心在 main 上提交了

# 1. 记下这次提交的哈希（假设是 abc123）
git log --oneline -1

# 2. 切换到正确的分支
git switch feature

# 3. 把提交搬过来
git cherry-pick abc123

# 4. 回到 main，撤销那个提交
git switch main
git reset --hard HEAD~1       # ⚠️ 仅当未推送时使用
```

### 场景 6：Pull 时发生冲突

```bash
# 1. 先暂存本地修改
git stash

# 2. 拉取远程更新
git pull origin main

# 3. 恢复本地修改（可能有冲突）
git stash pop

# 4. 手动解决冲突后
git add .
git commit -m "合并远程更新，解决冲突"
```

### 场景 7：想放弃本地所有修改，和远程保持一致

```bash
git fetch origin
git reset --hard origin/main
```

> ⚠️ 会丢弃所有本地修改，执行前确认没有需要保留的内容。

### 场景 8：本地有一个文件不想提交，但也不想加到 .gitignore

```bash
# 告诉 Git 忽略该文件的本地修改
git update-index --assume-unchanged 文件名

# 恢复追踪
git update-index --no-assume-unchanged 文件名
```

### 场景 9：提交历史太乱，想把最近几次提交合并

```bash
# 将最近 3 次提交压缩为一个
git rebase -i HEAD~3

# 在编辑器中，保留第一个 pick，将后面两个改为 squash
```

### 场景 10：想临时回到之前的某个版本看看代码

```bash
# 以"分离 HEAD"状态查看历史版本（可以看，但不能直接改）
git checkout 提交哈希

# 看完后回到原来的分支
git switch main
```

---

## 16. 最佳实践与习惯

### 16.1 提交粒度

- **一次提交做一件事**：不要在一个提交里既修 bug 又加新功能又改文档
- **小步提交，频繁推送**：每个逻辑单元提交一次，方便以后查找和回退
- **提交信息写清楚"做了什么"**：不要写"update"，写"修复排序算法中的指针越界问题"

### 16.2 分支使用

- `main` 分支保持稳定可运行
- 新功能、实验性修改在单独的分支上做
- 合并前确保代码能正常运行
- 合并后及时删除无用的分支

### 16.3 同步习惯

```bash
# 每天开始工作前
git pull origin main

# 每天结束工作后
git add .
git commit -m "日期 + 内容描述"
git push origin main
```

### 16.4 安全操作原则

| ❌ 不要 | ✅ 应该 |
| --- | --- |
| 对共享分支使用 `git push --force` | 使用 `--force-with-lease` 或 `revert` |
| 对已推送的提交使用 `rebase` | 仅在本地未推送的提交上 rebase |
| 使用 `git reset --hard` 前不确认 | 先用 `git log` 确认，或先用 `git stash` 备份 |
| 提交密钥、密码等敏感信息 | 使用 `.gitignore` 排除 `.env` 等敏感文件 |
| 提交编译产物（exe、o 等） | 配置好 `.gitignore` |

### 16.5 常用别名推荐

在 `~/.gitconfig` 或执行以下命令添加别名，大幅提高效率：

```bash
git config --global alias.st status
git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.ci commit
git config --global alias.lg "log --oneline --graph --all -20"
git config --global alias.last "log -1 HEAD --stat"
git config --global alias.unstage "restore --staged"
git config --global alias.discard "restore"
```

### 16.6 日常检查清单

每天提交前快速确认：

1. `git status` — 看看有哪些改动，有没有不该提交的文件
2. `git diff --staged` — 确认要提交的内容是否和预期一致
3. `.gitignore` 是否忽略了该忽略的文件
4. 提交信息是否清晰描述了改动
5. `git pull` 后再 `git push`（如果是协作仓库）

---

## 17. Git 托管平台差异

### 主要平台对比

| 平台 | 特点 | 适用场景 |
| --- | --- | --- |
| **GitHub** | 全球最大开源社区，生态最完善 | 开源项目、个人项目、国际协作 |
| **GitLab** | 自带 CI/CD，可私有部署 | 企业项目、DevOps |
| **Gitee（码云）** | 国内访问快，中文界面 | 国内项目、学生作业 |
| **Coding** | 国内平台，集成 DevOps 工具链 | 国内团队协作 |

### 平台特有功能

| 功能 | GitHub | GitLab | Gitee |
| --- | --- | --- | --- |
| Pull Request / Merge Request | ✅ Pull Request | ✅ Merge Request | ✅ Pull Request |
| GitHub Pages（静态网站） | ✅ | ❌（用 GitLab Pages） | ✅ Gitee Pages |
| GitHub Actions（CI/CD） | ✅ | ❌（用 GitLab CI） | ❌ |
| 私有仓库 | ✅ 免费 | ✅ 免费 | ✅ 免费 |
| Wiki | ✅ | ✅ | ✅ |
| Issue 追踪 | ✅ | ✅ | ✅ |
| 代码片段（Gist） | ✅ | ✅ Snippets | ❌ |

### 同时推送到多个平台

如果你的项目需要同时托管在 GitHub 和 Gitee：

```bash
# 添加多个远程仓库
git remote add github https://github.com/用户名/仓库名.git
git remote add gitee https://gitee.com/用户名/仓库名.git

# 推送到 GitHub
git push github main

# 推送到 Gitee
git push gitee main

# 或者修改默认 origin 的 URL 实现一键推送
# （需要先设置多个 pushurl）
git remote set-url --add --push origin https://github.com/用户名/仓库名.git
git remote set-url --add --push origin https://gitee.com/用户名/仓库名.git
# 之后 git push 会同时推送到两个平台
```

---

> **📝 教程结束** — 本教程涵盖了 Git 从入门到日常使用的核心内容。
>
> **建议学习路径**：
> 1. 先看 [日常推送.md](日常推送.md) 掌握基本推送流程
> 2. 通读本教程的前 8 节（1~8），建立完整的 Git 知识框架
> 3. 在实际使用中遇到问题，回来查阅第 15 节（常见场景速查）
> 4. 需要团队协作时，重点看第 6、13 节
>
> **进一步学习资源**：
> - [Pro Git（中文版）](https://git-scm.com/book/zh/v2) — 官方免费书籍，最权威的 Git 学习资料
> - [GitHub Skills](https://skills.github.com/) — GitHub 官方互动教程
> - [Learn Git Branching](https://learngitbranching.js.org/) — 可视化学习分支操作
> - [Oh Shit, Git!?!](https://ohshitgit.com/) — 常见翻车场景自救指南
> - [Conventional Commits](https://www.conventionalcommits.org/zh-hans/) — 提交信息规范
