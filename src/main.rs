use std::fs;
use clap::{Parser};
use ltxlog::parse;

/// A simple CLI tool for parsing and summarizing errors and warnings in LaTeX logs.
#[derive(Parser, Debug)]
#[command(version, about, long_about = None)]
struct Args {
    #[arg(short, long, default_value_t=String::from("master.log"))]
    file_path: String,
}

fn main() {
    let args: Args = Args::parse();
    run(&args);
}

fn run(args: &Args) {
    let contents = fs::read_to_string(&args.file_path)
                      .expect("Couldn't open log file");
    let result = parse(&contents);
    let _ = dbg!(result);
}
