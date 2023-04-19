# Data files in cpp-stat-bench (version 1)

*JSON schema of data files written by cpp-stat-bench library  (version 1).*

## Properties

- **`started_at`** *(string)*: Time when this benchmark execution started.
- **`finished_at`** *(string)*: Time when this benchmark execution finished.
- **`measurements`** *(array)*: List of information of measurements of time.
  - **Items** *(object)*: Information of a measurement of time.
    - **`group_name`** *(string)*: Name of the group in the benchmark.
    - **`case_name`** *(string)*: Name of the case in the benchmark.
    - **`params`** *(object)*: Parameters of this measurement.
      - **`^.*$`** *(string)*: Parameter of this measurement.
    - **`measurer_name`** *(string)*: Name of the measurer of this measurement.
    - **`iterations`** *(integer)*: Number of iterations in each iteration.
    - **`samples`** *(integer)*: Number of samples.
    - **`custom_outputs`** *(array)*: List of user-specified outputs.
      - **Items** *(object)*: User-specified output.
        - **`name`** *(string)*: Name of the custom output.
        - **`value`** *(number)*: Value of the custom output.
    - **`custom_stat_outputs`** *(array)*: List of user-specified outputs with statistics.
      - **Items** *(object)*: User-specified output with statistics.
        - **`name`** *(string)*: Name of the custom output.
        - **`stat`** *(object)*: Statistics of the custom output.
          - **`max`** *(number)*: Maximum value of the custom output.
          - **`mean`** *(number)*: Mean value of the custom output.
          - **`min`** *(number)*: Minimum value of the custom output.
          - **`standard_deviation`** *(number)*: Standard deviation of values of the custom output.
          - **`variance`** *(number)*: Variance of values of the custom output.
        - **`values`** *(array)*: Values of the custom output.
          - **Items** *(array)*: Values of the custom output.
            - **Items** *(number)*: Value of the custom output.
    - **`durations`** *(object)*: Measured durations.
      - **`stat`** *(object)*: Statistics of the measured durations.
        - **`max`** *(number)*: Maximum duration.
        - **`mean`** *(number)*: Mean duration.
        - **`min`** *(number)*: Minimum duration.
        - **`standard_deviation`** *(number)*: Standard deviation of the durations.
        - **`variance`** *(number)*: Variance of the durations.
      - **`values`** *(array)*: Values of the measured durations.
        - **Items** *(array)*: Values of the measured durations.
          - **Items** *(number)*: Value of a measured duration.
