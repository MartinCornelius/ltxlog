// Works by having a vector of files that contains a vector of errors.
use std::error::Error;

#[derive(Clone, Debug)]
pub struct LogEvent<'a> {
    file_name: &'a str,
    errors: Vec<&'a str>,
}

pub fn parse<'a>(contents: &'a str) -> Result<Vec<LogEvent<'a>>, Box<dyn Error>> {
    let mut event_stack: Vec<LogEvent> = Vec::new();
    let mut result: Vec<LogEvent> = Vec::new();

    for line in contents.lines() {
        // Check for entering a file (if not closed on same line)
        if line.starts_with("(") && !line.contains(")") {
            event_stack.push(LogEvent{file_name: line, errors: Vec::new() });
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
                .push(line);
        }
    }
    // Pushing master.log (or main log file) to the results
    if event_stack.len() == 1 {
        result.push(event_stack.pop().unwrap());
    }

    Ok(result)
}
