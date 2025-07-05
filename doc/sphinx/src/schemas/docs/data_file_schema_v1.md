# Data files in cpp-stat-bench (version 1)

*JSON schema of data files written by cpp-stat-bench library  (version 1).*

## Properties

- <a id="properties/started_at"></a>**`started_at`** *(string, required)*: Time when this benchmark execution started.
- <a id="properties/finished_at"></a>**`finished_at`** *(string, required)*: Time when this benchmark execution finished.
- <a id="properties/measurements"></a>**`measurements`** *(array, required)*: List of information of measurements of time.
  - <a id="properties/measurements/items"></a>**Items** *(object)*: Information of a measurement of time.
    - <a id="properties/measurements/items/properties/group_name"></a>**`group_name`** *(string, required)*: Name of the group in the benchmark.
    - <a id="properties/measurements/items/properties/case_name"></a>**`case_name`** *(string, required)*: Name of the case in the benchmark.
    - <a id="properties/measurements/items/properties/params"></a>**`params`** *(object, required)*: Parameters of this measurement.
      - <a id="properties/measurements/items/properties/params/patternProperties/%5E.%2A%24"></a>**`^.*$`** *(string)*: Parameter of this measurement.
    - <a id="properties/measurements/items/properties/measurer_name"></a>**`measurer_name`** *(string, required)*: Name of the measurer of this measurement.
    - <a id="properties/measurements/items/properties/iterations"></a>**`iterations`** *(integer, required)*: Number of iterations in each iteration.
    - <a id="properties/measurements/items/properties/samples"></a>**`samples`** *(integer, required)*: Number of samples.
    - <a id="properties/measurements/items/properties/custom_outputs"></a>**`custom_outputs`** *(array, required)*: List of user-specified outputs.
      - <a id="properties/measurements/items/properties/custom_outputs/items"></a>**Items** *(object)*: User-specified output.
        - <a id="properties/measurements/items/properties/custom_outputs/items/properties/name"></a>**`name`** *(string, required)*: Name of the custom output.
        - <a id="properties/measurements/items/properties/custom_outputs/items/properties/value"></a>**`value`** *(number, required)*: Value of the custom output.
    - <a id="properties/measurements/items/properties/custom_stat_outputs"></a>**`custom_stat_outputs`** *(array, required)*: List of user-specified outputs with statistics.
      - <a id="properties/measurements/items/properties/custom_stat_outputs/items"></a>**Items** *(object)*: User-specified output with statistics.
        - <a id="properties/measurements/items/properties/custom_stat_outputs/items/properties/name"></a>**`name`** *(string, required)*: Name of the custom output.
        - <a id="properties/measurements/items/properties/custom_stat_outputs/items/properties/stat"></a>**`stat`** *(object, required)*: Statistics of the custom output.
          - <a id="properties/measurements/items/properties/custom_stat_outputs/items/properties/stat/properties/max"></a>**`max`** *(number, required)*: Maximum value of the custom output.
          - <a id="properties/measurements/items/properties/custom_stat_outputs/items/properties/stat/properties/mean"></a>**`mean`** *(number, required)*: Mean value of the custom output.
          - <a id="properties/measurements/items/properties/custom_stat_outputs/items/properties/stat/properties/min"></a>**`min`** *(number, required)*: Minimum value of the custom output.
          - <a id="properties/measurements/items/properties/custom_stat_outputs/items/properties/stat/properties/standard_deviation"></a>**`standard_deviation`** *(number, required)*: Standard deviation of values of the custom output.
          - <a id="properties/measurements/items/properties/custom_stat_outputs/items/properties/stat/properties/variance"></a>**`variance`** *(number, required)*: Variance of values of the custom output.
        - <a id="properties/measurements/items/properties/custom_stat_outputs/items/properties/values"></a>**`values`** *(array, required)*: Values of the custom output.
          - <a id="properties/measurements/items/properties/custom_stat_outputs/items/properties/values/items"></a>**Items** *(array)*: Values of the custom output.
            - <a id="properties/measurements/items/properties/custom_stat_outputs/items/properties/values/items/items"></a>**Items** *(number)*: Value of the custom output.
    - <a id="properties/measurements/items/properties/durations"></a>**`durations`** *(object, required)*: Measured durations.
      - <a id="properties/measurements/items/properties/durations/properties/stat"></a>**`stat`** *(object, required)*: Statistics of the measured durations.
        - <a id="properties/measurements/items/properties/durations/properties/stat/properties/max"></a>**`max`** *(number, required)*: Maximum duration.
        - <a id="properties/measurements/items/properties/durations/properties/stat/properties/mean"></a>**`mean`** *(number, required)*: Mean duration.
        - <a id="properties/measurements/items/properties/durations/properties/stat/properties/min"></a>**`min`** *(number, required)*: Minimum duration.
        - <a id="properties/measurements/items/properties/durations/properties/stat/properties/standard_deviation"></a>**`standard_deviation`** *(number, required)*: Standard deviation of the durations.
        - <a id="properties/measurements/items/properties/durations/properties/stat/properties/variance"></a>**`variance`** *(number, required)*: Variance of the durations.
      - <a id="properties/measurements/items/properties/durations/properties/values"></a>**`values`** *(array, required)*: Values of the measured durations.
        - <a id="properties/measurements/items/properties/durations/properties/values/items"></a>**Items** *(array)*: Values of the measured durations.
          - <a id="properties/measurements/items/properties/durations/properties/values/items/items"></a>**Items** *(number)*: Value of a measured duration.
