# Data files in cpp-stat-bench (version 2)

*JSON schema of data files written by cpp-stat-bench library  (version 2).*

## Properties

- **`started_at`** *(string, required)*: Time when this benchmark execution started.
- **`finished_at`** *(string, required)*: Time when this benchmark execution finished.
- **`measurements`** *(array, required)*: List of information of measurements of time.
  - **Items** *(object)*: Information of a measurement of time.
    - **`group_name`** *(string, required)*: Name of the group in the benchmark.
    - **`case_name`** *(string, required)*: Name of the case in the benchmark.
    - **`params`** *(object, required)*: Parameters of this measurement.
      - **`^.*$`** *(string)*: Parameter of this measurement.
    - **`measurer_name`** *(string, required)*: Name of the measurer of this measurement.
    - **`iterations`** *(integer, required)*: Number of iterations in each iteration.
    - **`samples`** *(integer, required)*: Number of samples.
    - **`custom_outputs`** *(array, required)*: List of user-specified outputs.
      - **Items** *(object)*: User-specified output.
        - **`name`** *(string, required)*: Name of the custom output.
        - **`value`** *(number, required)*: Value of the custom output.
    - **`custom_stat_outputs`** *(array, required)*: List of user-specified outputs with statistics.
      - **Items** *(object)*: User-specified output with statistics.
        - **`name`** *(string, required)*: Name of the custom output.
        - **`stat`** *(object, required)*: Statistics of the custom output.
          - **`max`** *(number, required)*: Maximum value of the custom output.
          - **`mean`** *(number, required)*: Mean value of the custom output.
          - **`min`** *(number, required)*: Minimum value of the custom output.
          - **`median`** *(number, required)*: Median of the custom output.
          - **`standard_deviation`** *(number, required)*: Standard deviation of values of the custom output.
          - **`variance`** *(number, required)*: Variance of values of the custom output.
          - **`standard_error`** *(number, required)*: Standard error of values of the custom output.
        - **`values`** *(array, required)*: Values of the custom output.
          - **Items** *(array)*: Values of the custom output.
            - **Items** *(number)*: Value of the custom output.
    - **`durations`** *(object, required)*: Measured durations.
      - **`stat`** *(object, required)*: Statistics of the measured durations.
        - **`max`** *(number, required)*: Maximum duration.
        - **`mean`** *(number, required)*: Mean duration.
        - **`min`** *(number, required)*: Minimum duration.
        - **`median`** *(number, required)*: Median of the custom output.
        - **`standard_deviation`** *(number, required)*: Standard deviation of the durations.
        - **`variance`** *(number, required)*: Variance of the durations.
        - **`standard_error`** *(number, required)*: Standard error of values of the custom output.
      - **`values`** *(array, required)*: Values of the measured durations.
        - **Items** *(array)*: Values of the measured durations.
          - **Items** *(number)*: Value of a measured duration.
