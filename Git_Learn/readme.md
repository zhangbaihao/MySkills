常见的Git命令和操作：

1. 初始化仓库：
   ```shell
   git init
   ```

2. 克隆远程仓库：
   ```shell
   git clone <repository_url>
   ```

3. 查看文件状态：
   ```shell
   git status
   ```

4. 添加文件到暂存区：
   ```shell
   git add <file_name>
   ```

5. 提交暂存区的文件：
   ```shell
   git commit -m "commit message"
   ```

6. 查看提交历史：
   ```shell
   git log
   ```

7. 切换分支：
   ```shell
   git checkout <branch_name>
   ```

8. 创建并切换到新分支：
   ```shell
   git checkout -b <branch_name>
   ```

9. 拉取远程分支到本地：
   ```shell
   git pull origin <branch_name>
   ```

10. 推送本地分支到远程：
    ```shell
    git push origin <branch_name>
    ```

11. 合并分支：
    ```shell
    git merge <branch_name>
    ```

12. 撤销工作区的修改：
    ```shell
    git checkout -- <file_name>
    ```

13. 撤销暂存区的修改：
    ```shell
    git reset HEAD <file_name>
    ```

14. 回滚到指定的提交：
    ```shell
    git revert <commit_id>
    ```


要使`.gitignore`文件的修改生效，您可以按照以下步骤操作：
1. 使用`git rm`命令删除已经被Git跟踪的文件和文件夹。该命令会将这些文件从Git的索引中移除，但不会删除实际的文件。运行以下命令：
   ```shell
   git rm -r --cached .
   ```

2. 使用`git add`命令将`.gitignore`文件添加到Git的索引中，以便将其纳入版本控制。运行以下命令：
   ```shell
   git add .gitignore
   ```

3. 最后，使用`git commit`命令提交变更并添加一条描述性的提交消息。运行以下命令：
   ```shell
   git commit -m "Update .gitignore"
   ```

这样，`.gitignore`文件中的修改将生效，并且Git将会忽略相应的文件和文件夹。

另外，如果您在`.gitignore`文件中添加了规则后，希望将其应用于已经被Git跟踪的文件，可以使用`git rm`命令将这些文件从Git的索引中删除，并且在下一次提交时它们将被忽略。但请注意，这将会删除实际的文件。运行以下命令：
```shell
git rm --cached <file_path>
```
将`<file_path>`替换为要删除的文件路径。例如，要删除`src/example.txt`文件，可以运行以下命令：
```shell
git rm --cached src/example.txt
```