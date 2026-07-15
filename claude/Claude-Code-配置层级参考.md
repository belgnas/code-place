# Claude Code 配置层级参考

## 三层架构

```
项目级 .claude/          ← 优先级最高（手动创建，仅影响当前项目）
      ↓ 覆盖
用户级 ~/.claude/        ← 中等优先级（Claude 自动创建，影响所有项目）
      ↓ 兜底
Claude Code 内置默认值    ← 最低优先级
```

> **判断标准**：换一个项目，这个配置还有意义吗？→ 有 = 用户级 / 没有 = 项目级

---

## 一、Claude Code 内置默认值

无需任何配置，开箱即用的行为。你感知不到这一层，但它始终在底层兜底。

| 内容 | 说明 |
|------|------|
| 默认权限策略 | 写文件、执行命令等危险操作默认弹窗确认 |
| 默认模型参数 | token 上限、温度等 |
| 内置 skill | `dataviz`、`deep-research`、`code-review` 等 |
| 内置 agent 类型 | `general-purpose`、`Explore`、`Plan` 等 |
| UI 行为 | 终端交互方式、输出格式等 |

---

## 二、用户级 `~/.claude/`（全局）

> **自动创建**，第一次运行 Claude Code 时生成。影响本机上所有项目。

### 目录结构

```
~/.claude/
├── settings.json          ← 全局配置文件（手动编辑或用 /config 命令）
├── settings.local.json    ← 本地覆盖（不提交，优先级高于 settings.json）
├── history.jsonl          ← 命令历史（自动维护）
├── sessions/              ← 历史对话记录（自动维护）
├── cache/                 ← 缓存（自动维护）
├── plugins/               ← 已安装的插件
└── backups/               ← 备份
```

### 适合放用户级的内容

| 配置类型 | 具体示例 | 原因 |
|----------|---------|------|
| **API 密钥 / 端点** | `ANTHROPIC_AUTH_TOKEN`、`ANTHROPIC_BASE_URL`、自定义模型名 | 跟人绑定，不跟项目走 |
| **模型偏好** | 默认使用的 Sonnet/Opus/Haiku 模型 | 个人偏好，所有项目一样 |
| **通用权限** | `Bash(ls *)`、`Bash(git status *)` 等只读操作 | 所有项目都需要的安全操作 |
| **通用 hook** | "每次对话结束自动备份"、"新对话时加载自定义提示词" | 跟具体项目无关的工作流 |
| **第三方插件** | 从插件市场安装的通用插件 | 跨项目复用 |
| **UI 偏好** | 主题、输出风格、通知设置 | 纯个人喜好 |

### 不适合放用户级的内容

- 跟某个项目技术栈绑定的 skill
- 项目专属的权限 deny 规则
- 团队共享的 agent 定义

---

## 三、项目级 `<项目>/.claude/`（项目专属）

> **手动创建**，你决定要不要。需要提交到 Git 时**注意不要泄露密钥**。

### 目录结构

```
项目/.claude/
├── settings.json          ← 项目级配置（权限、hook、env 等）
├── agents/                ← 自定义子代理定义
│   └── algo-reviewer.md   ← 示例：算法题解审查代理
├── workflows/             ← 可复用的工作流脚本
│   └── new-problem.js     ← 示例：新建算法题的标准化流程
├── commands/              ← 自定义斜杠命令
│   └── solve.md           ← 示例：/solve 命令
└── skills/                ← 项目专属 skill（特定领域知识）
    └── cph-helper.md      ← 示例：CPH 插件辅助 skill
```

### 适合放项目级的内容

| 配置类型 | 具体示例 | 原因 |
|----------|---------|------|
| **项目专属权限 deny** | 禁止写入 `.cph/`、`output/`、`__pycache__/` | 只在这个项目有意义 |
| **项目专属权限 allow** | 允许 `Bash(cph submit *)` 等 CPH 命令 | 换一个项目就不适用 |
| **Skill** | 算法竞赛流程 skill、CPH 插件辅助 skill | 跟项目技术栈绑定 |
| **Hook** | "提交前编译检查 C++ 代码"、"新建 `.cpp` 时自动创建同名 `.md`" | 行为跟项目强相关 |
| **Agent** | "算法题解 review agent"、"C++ 代码风格检查 agent" | 针对项目需求定制 |
| **Workflow** | "新建一场 CF 比赛题解"的标准化流程 | 项目特定工作流 |
| **Custom commands** | `/new-problem`、`/batch-solve` | 项目专属快捷操作 |
| **项目环境变量** | `CPH_DIR`、`BUILD_OUTPUT_DIR` | 项目构建相关 |
| **团队共享规则** | 统一的权限策略、代码规范检查 | 提交到 Git 让全队使用 |

### 注意

- `.claude/` 目录默认**不在 `.gitignore` 中**，提交时注意不要泄露 API 密钥等敏感信息
- 如果只给自己用、不提交，可以把敏感配置放 `.claude/settings.local.json`（记得加到 `.gitignore`）

---

## 四、`CLAUDE.md`（项目说明文件）

> 位于项目根目录，**手动编写**，Claude 进入项目时自动读取。

| 内容 | 示例 |
|------|------|
| 项目概述 | 项目是做什么的、用什么技术栈 |
| 目录结构 | 各文件夹的含义 |
| 命名规范 | 文件/目录的命名约定 |
| 编码风格 | 注释风格、代码格式偏好 |
| 对 Claude 的要求 | "中文优先"、"不要向缓存目录写文件" |

---

## 五、快速对照表

| 我想…… | 放哪里 |
|---------|--------|
| 告诉 Claude 这个项目是干什么的 | 项目根目录 `CLAUDE.md` |
| 设置 API 密钥、换模型 | 用户级 `~/.claude/settings.json` |
| 允许所有项目免确认执行 `git status` | 用户级 `~/.claude/settings.json` |
| 禁止在这个项目里碰 `.cph/` 目录 | 项目级 `.claude/settings.json` |
| 新建算法题时自动创建 `.cpp` + `.md` | 项目级 `.claude/settings.json`（hook） |
| 写一个 "算法题解审查" 的 agent | 项目级 `.claude/agents/` |
| 自定义 `/solve` 命令一键做题 | 项目级 `.claude/commands/` |
| 做一个 "补全 CF 比赛题解" 的标准化流程 | 项目级 `.claude/workflows/` |
| 换主题/通知偏好 | 用户级 `~/.claude/settings.json` |
| 共享权限策略给团队成员 | 项目级 `.claude/settings.json`（提交到 Git） |
