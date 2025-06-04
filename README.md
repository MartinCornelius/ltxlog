# ltxlog

**ltxlog** is a simple CLI tool that parses LaTeX `.log` files and summarizes relevant error messages.

## Features

- Extracts and prints LaTeX error messages
- Shows the relevant line from `.tex` source files
- Supports custom log and source directories

## Usage

```sh
ltxlog [options]
```

| Option            | Description                           |
| ----------------- | ------------------------------------- |
| `--workdir DIR`   | Path to the root of your `.tex` files |
| `--outdir DIR`    | Directory containing the `.log` file  |
| `--log-name NAME` | Name of the `.log` file (omit `.log`) |
| `--version`       | Show version information              |
| `--help`          | Show usage information                |

### Example
```sh
ltxlog --workdir src --outdir build --log-name main
```

### Installation
```sh
make
sudo make install
```
Installs to `/usr/local/bin/ltxlog` by default.
To install locally (no `sudo` required):
```sh
make install PREFIX=$HOME
```

### Uninstall
```sh
sudo make uninstall
```