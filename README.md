# git-sync - Sync a branch with a remote using a worktre

The `git-sync` is a custom Git extension, developed in C/C++.

This command has 3 abilities;

#### Sync (default)

Will perform a push/pull for the current branch
```sh
> git sync
```


#### Sync Rebase
Rebase using the Tracked Worktree branch
```sh
> git sync rebase
```


#### Sync Merge
Merge using the Tracked Worktree branch
```sh
> git sync merge
```


#### CLI Commands
    git-sync <OPTIONS>

