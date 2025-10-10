#!/bin/bash

# Define the test executable and output directories
TEST_EXECUTABLE="./DSA_Test"
COVERAGE_INFO="coverage.info"
COVERAGE_FILTERED_INFO="coverage_filtered.info"
COVERAGE_OUTPUT_DIR="coverage_report"

# Run the test executable
echo "Running test executable..."
$TEST_EXECUTABLE

# Capture coverage data, ignoring mismatched end line errors and other warnings
echo "Capturing coverage data..."
lcov --capture --directory . --output-file $COVERAGE_INFO --ignore-errors mismatch,empty

# Remove unnecessary files, including specific paths, ignoring empty tracefile errors
echo "Removing unnecessary files from coverage data..."
lcov --remove $COVERAGE_INFO '/usr/*' \
    --remove $COVERAGE_INFO '*/googletest/googletest/include/gtest/*' \
    --remove $COVERAGE_INFO '*/googletest/googletest/include/gtest/internal/*' \
    --remove $COVERAGE_INFO '*/Test/*' \
    --output-file $COVERAGE_FILTERED_INFO --ignore-errors empty

# Generate HTML report
echo "Generating HTML coverage report..."
genhtml $COVERAGE_FILTERED_INFO --output-directory $COVERAGE_OUTPUT_DIR --ignore-errors mismatch,empty

echo "Coverage report generated in $COVERAGE_OUTPUT_DIR"
