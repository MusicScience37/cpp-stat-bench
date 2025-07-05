# Data files in cpp-stat-bench (version 2)

_JSON schema of data files written by cpp-stat-bench library (version 2)._

## Properties

- **`started_at`** _(string, required)_: Time when this benchmark execution started.
- **`finished_at`** _(string, required)_: Time when this benchmark execution finished.
- **`measurements`** _(array, required)_: List of information of measurements of time.
  - **Items** _(object)_: Information of a measurement of time.
    - **`group_name`** _(string, required)_: Name of the group in the benchmark.
    - **`case_name`** _(string, required)_: Name of the case in the benchmark.
    - **`params`** _(object, required)_: Parameters of this measurement.
      - **`^.*$`** _(string)_: Parameter of this measurement.
    - **`measurement_type`** _(string, required)_: Name of the measurer of this measurement.
    - **`iterations`** _(integer, required)_: Number of iterations in each iteration.
    - **`samples`** _(integer, required)_: Number of samples.
    - **`custom_outputs`** _(array, required)_: List of user-specified outputs.
      - **Items** _(object)_: User-specified output.
        - **`name`** _(string, required)_: Name of the custom output.
        - **`value`** _(number, required)_: Value of the custom output.
    - **`custom_stat_outputs`** _(array, required)_: List of user-specified outputs with statistics.
      - **Items** _(object)_: User-specified output with statistics.
        - **`name`** _(string, required)_: Name of the custom output.
        - **`stat`** _(object, required)_: Statistics of the custom output.
          - **`max`** _(number, required)_: Maximum value of the custom output.
          - **`mean`** _(number, required)_: Mean value of the custom output.
          - **`min`** _(number, required)_: Minimum value of the custom output.
          - **`median`** _(number, required)_: Median of the custom output.
          - **`standard_deviation`** _(number, required)_: Standard deviation of values of the custom output.
          - **`variance`** _(number, required)_: Variance of values of the custom output.
          - **`standard_error`** _(number, required)_: Standard error of values of the custom output.
        - **`values`** _(array, required)_: Values of the custom output.
          - **Items** _(array)_: Values of the custom output.
            - **Items** _(number)_: Value of the custom output.
    - **`durations`** _(object, required)_: Measured durations.
      - **`stat`** _(object, required)_: Statistics of the measured durations.
        - **`max`** _(number, required)_: Maximum duration.
        - **`mean`** _(number, required)_: Mean duration.
        - **`min`** _(number, required)_: Minimum duration.
        - **`median`** _(number, required)_: Median of the custom output.
        - **`standard_deviation`** _(number, required)_: Standard deviation of the durations.
        - **`variance`** _(number, required)_: Variance of the durations.
        - **`standard_error`** _(number, required)_: Standard error of values of the custom output.
      - **`values`** _(array, required)_: Values of the measured durations.
        - **Items** _(array)_: Values of the measured durations.
          - **Items** _(number)_: Value of a measured duration.
