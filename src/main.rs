use clap::{Parser};
use ltxlog::{Config, parse, update_src_lines};

fn main() {
    let config: Config = Config::parse();
    run(&config);
}

fn run(config: &Config) {
    let mut result = parse(config).unwrap();

    if config.full {
        update_src_lines(&mut result);
        ltxlog::report_full(&result);
    } else {
        ltxlog::report_short(&result);
    }
}
