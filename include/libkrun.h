#include <inttypes.h>

/*
 * Sets the log level for the library.
 *
 * Arguments:
 *  "level" can be one of the following values:
 *    0: Off
 *    1: Error
 *    2: Warn
 *    3: Info
 *    4: Debug
 *    5: Trace
 *
 * Returns:
 *  Zero on success or a negative error number on failure.
 */
int32_t krun_set_log_level(uint32_t level);

/*
 * Creates a configuration context.
 *
 * Returns:
 *  The context ID on success or a negative error number on failure.
 */
int32_t krun_create_ctx();

/*
 * Frees an existing configuration context.
 *
 * Arguments:
 *  "ctx_id" - the configuration context ID.
 *
 * Returns:
 *  Zero on success or a negative error number on failure.
 */
int32_t krun_free_ctx(uint32_t ctx_id);

/*
 * Sets the basic configuration parameters for the microVM.
 *
 * Arguments:
 *  "ctx_id"    - the configuration context ID.
 *  "num_vcpus" - the number of vCPUs.
 *  "ram_mib"   - the amount of RAM in MiB.
 *
 * Returns:
 *  Zero on success or a negative error number on failure.
 */
int32_t krun_set_vm_config(uint32_t ctx_id, uint8_t num_vcpus, uint32_t ram_mib);

/*
 * Sets the path to be use as root for the microVM.
 *
 * Arguments:
 *  "ctx_id"    - the configuration context ID.
 *  "root_path" - a null-terminated string representing the path to be used as root.
 *
 * Returns:
 *  Zero on success or a negative error number on failure.
 */
int32_t krun_set_root(uint32_t ctx_id, const char *root_path);

/*
 * Sets the path to the executable to be run inside the microVM, the arguments to be passed to the
 * executable, and the environment variables to be configured in the context of the executable.
 *
 * Arguments:
 *  "ctx_id"    - the configuration context ID.
 *  "exec_path" - the path to the executable, relative to the root configured with "krun_set_root".
 *  "argv"      - an array of string pointers to be passed as arguments.
 *  "envp"      - an array of string pointers to be injected as environment variables into the
 *                context of the executable. If NULL, it will auto-generate an array collecting the
 *                the variables currently present in the environment.
 *
 * Returns:
 *  Zero on success or a negative error number on failure.
 */
int32_t krun_set_exec(uint32_t ctx_id,
                      const char *exec_path,
                      char *const argv[],
                      char *const envp[]);

/*
 * Starts and enters the microVM with the configured parameters. The VMM will attempt to take over
 * stdin/stdout to manage them on behalf of the process running inside the isolated environment,
 * simulating that the latter has direct control of the terminal.
 *
 * This function consumes the configuration pointed by the context ID.
 *
 * Arguments:
 *  "ctx_id" - the configuration context ID.
 *
 * Returns:
 *  This function only returns if an error happens before starting the microVM. Otherwise, the
 *  VMM assumes it has full control of the process, and will call to exit() once the microVM shuts
 *  down.
 */
int32_t krun_start_enter(uint32_t ctx_id);
