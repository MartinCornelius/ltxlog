# ltxlog

A source-aware LaTeX log tracer.

`ltxlog` reduces the noise of LaTeX logs to provide a structured view of
errors. It tracks file inclusions and maps errors back to your source code.

## Key Features
- **File Stack Tracking**: Attributes errors to nested `.tex` files.
- **Source Context**: Pulls the actual lines from your source files to show you
  exactly where the error occurred.

## Usage
```bash
ltxlog <filepath> [options]
```

Make sure you call `ltxlog` from the root directory of your latex project to
get the full features.

#### Examples
```bash
# Basic summary of master.log
ltxlog master.log

# Full report with source context
ltxlog master.log -f 
```

#### Options
- `-f` or `--full`: prints the full summary with source file context.

## Installation
```bash
git clone https://github.com/martincornelius/ltxlog
cd ltxlog
cargo install --path .
```
