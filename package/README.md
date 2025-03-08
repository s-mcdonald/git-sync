# README

## Build
Builds will be conducted by make, but if you have to follow the steps below.

Build command

1. `cd` into the package dir.
2. Run the following.

```
 dpkg-deb --build ./git-sync/
```
## Dev install

```sh
sudo dpkg -i git-sync.deb
```

## To uninstall

```sh
sudo dpkg -r git-sync
```
