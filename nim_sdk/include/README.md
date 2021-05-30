# NIM cross-platform SDK

NetEase-IM cross-platform SDK project managed by CMake and Conan

## 开发配置

NetEase IM G1 仓库在经过改造后使用 CMake + Conan 来管理项目工程和依赖的三方库。您可以使用 Visual Studio Code、Xcode、Visual Studio 等 IDE 来做日常开发。开发环境的初始化详细配置，请参考 Wiki：[如何配置开发环境](https://g.hz.netease.com/nim-pc/california/nim-cross-platform-sdk/-/wikis/Development/Setup-development-enviroment)

## Git 工作流

新仓库的 Git 工作流采用 git flow，简单来说 master 分支作为当前最新稳定代码分支。新的版本迭代过程中，我们基于 develop 开出新的 feature/* 分支进行功能开发，当冒烟测试稳定后合并至 develop 分支。在一个版本所有 feature/* 分支都合并到 develop 准备集成测试时，基于 develop 开出 release/* 分支（星号代表发布版本号），回归完成后合并 release/* 到 develop 和 master 并按版本号创建一个最新的 tag。

对于 git flow 工作流有任何问题请参考以下内容：

 - [A successful Git branching model](https://nvie.com/posts/a-successful-git-branching-model/)
 - [Gitflow Workflow](https://www.atlassian.com/git/tutorials/comparing-workflows/gitflow-workflow)

任何打乱 git flow 工作流的行为都可能会造成仓库分支混乱、合并冲突等问题，如您的分支命名方式不是以 git flow 方式创建，将会导致 CI 在编译时无法获取正确的分支、版本等信息。或您开启新的分支并不是以 git flow 规定的方式创建将会导致一系列代码合并错误。

建议使用 [git-flow](https://github.com/nvie/gitflow) 命令行终端来做日常的开发而不是原生 git 指令来开启或合并分支。或使用集成了 git flow 工作流的客户端如 [SourceTree](https://www.sourcetreeapp.com/)、[SmartGit](https://www.syntevo.com/smartgit/) 等，这些客户端天然集成了通过 UI 来创建 feature、release、hotfix 等能力可以减少协同开发过程中的错误。

## 代码风格

仓库中存储了 clang-format 及 cpplint 代码格式化配置文件，clang-format 可以让我们在开发过程中就让代码保持一个良好的固定风格，cpplint 帮助我们进一步检查代码风格的缺陷，这将大大提升代码的可读性、风格一致性。请在您的 IDE 工具中配置好 clang-format 及 cpplint 的可执行文件来进行统一的代码格式化。
