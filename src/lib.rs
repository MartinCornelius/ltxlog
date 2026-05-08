// Works by having a vector of files that contains a vector of errors.
use std::{error::Error, fs};
use clap::Parser;
use owo_colors::OwoColorize;

#[derive(Clone, Debug)]
pub struct LogError {
    message: String,
    line: usize,

    // A few lines in the context of the source line of the error
    src_context: Vec<String>,
}

#[derive(Clone, Debug)]
pub struct LogEvent {
    file_name: String,
    errors: Vec<LogError>,
}

/// A simple CLI tool for parsing and summarizing errors and warnings in LaTeX logs.
#[derive(Parser, Debug)]
#[command(version, about, long_about = None)]
pub struct Config {
    /// Filepath to the main log file
    #[arg(default_value_t=String::from("master.log"))]
    file_path: String,

    /// If true, prints the full summary
    #[arg(short, long, default_value_t=false)]
    pub full: bool,
}

pub fn parse(config: &Config) -> Result<Vec<LogEvent>, Box<dyn Error>> {
    let contents = fs::read_to_string(&config.file_path)?;

    let mut event_stack: Vec<LogEvent> = Vec::new();
    let mut result: Vec<LogEvent> = Vec::new();

    for line in contents.lines() {
        // Check for entering a file (if not closed on same line)
        if line.starts_with("(") && !line.contains(")") {
            event_stack.push(LogEvent{file_name: line[1..].to_string(), errors: Vec::new() });
        }
        // Check for closing file
        if line.starts_with(")") {
            // Only add non-empty event to result
            if event_stack.last().unwrap().errors.len() != 0 {
                result.push(event_stack.pop().unwrap());
            } else {
                event_stack.pop();
            }
        }

        // Check for error and add to list
        if line.starts_with("!") {
            event_stack
                .last_mut()
                .unwrap()
                .errors
                .push(LogError{
                    message: line.to_string(),
                    line: 0,
                    src_context: Vec::new() 
                });
        }

        // If line number, assign to the latest error found
        if line.starts_with("l.") {
            // Handle the l.16 format, for detecting line numbers.
            let line_split_collection: Vec<&str> = line.split(' ').collect();
            let mut line_num: usize = line_split_collection[0][2..].parse().unwrap();

            let current_error = event_stack
                                    .last_mut().unwrap()
                                    .errors
                                    .last_mut().unwrap();

            // Hardcoded allignments of line numbers
            if current_error.message.contains('$') {
                line_num -= 1;
            }

            current_error.line = line_num;
        }
    }
    // Pushing master.log (or main log file) to the results
    if event_stack.len() == 1 {
        result.push(event_stack.pop().unwrap());
    }

    Ok(result)
}

pub fn update_src_lines(log_events: &mut Vec<LogEvent>) {
    for file in log_events {
        // Open the source file
        println!("Looking in file: {}", &file.file_name);
        let contents = fs::read_to_string(&file.file_name)
                                    .expect("Couldn't open source file");
        let lines: Vec<&str> = contents.lines().collect();

        for error in &mut file.errors {
            let line_idx = error.line.saturating_sub(1);
            let start = line_idx.saturating_sub(2);
            let end = (line_idx + 2).min(lines.len().saturating_sub(1));
            for i in start..=end {
                error.src_context.push(lines[i].to_string());
            }
        }
    }
}

pub fn report_full(events: &[LogEvent]) {
    if events.is_empty() {
        println!("\n{}", "No errors found! Your LaTeX is clean.".green().bold());
        return;
    }

    println!("\n{}", "LtxLog Error Report".bright_red().bold().underline());
    for event in events {
        println!("\nFile: {}", event.file_name.cyan().bold());
        println!("{}", "─".repeat(event.file_name.len() + 8).dimmed());

        for error in &event.errors {
            println!("  {} {}", "!".red().bold(), error.message.bright_white());
            if error.line > 0 {
                println!("  {} line {} {} {}", "at".dimmed(), error.line.yellow(), "->".cyan(), event.file_name.cyan());
                if !error.src_context.is_empty() {
                    println!();
                    for (i, line_text) in error.src_context.iter().enumerate() {
                        let display_line = (error.line as isize - 2 + i as isize) as usize;
                        if display_line == error.line {
                            println!("    {:>4} │ {}", display_line.red().bold(), line_text.bright_white());
                        } else {
                            println!("    {:>4} │ {}", display_line.dimmed(), line_text.dimmed());
                        }
                    }
                    println!();
                }
            }
            println!("{}", "  ┄┄┄".dimmed());
        }
    }
}

pub fn report_short(events: &[LogEvent]) {
    if events.is_empty() {
        println!("\n{}", "No errors found! Your LaTeX is clean.".green().bold());
        return;
    }

    println!("\n{}", "LtxLog Error Report".bright_red().bold().underline());
    for event in events {
        println!("\nFile: {}", event.file_name.cyan().bold());
        println!("{}", "─".repeat(event.file_name.len() + 8).dimmed());

        for error in &event.errors {
            println!("  {} {}", "!".red().bold(), error.message.bright_white());
            if error.line > 0 {
                println!("  {} line {} {} {}", "at".dimmed(), error.line.yellow(), "->".cyan(), event.file_name.cyan());
            }
            println!("{}", "  ┄┄┄".dimmed());
        }
    }
}
