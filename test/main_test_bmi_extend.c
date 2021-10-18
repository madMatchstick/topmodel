#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/topmodel.h" 
#include "../include/bmi.h" 
#include "../include/bmi_topmodel.h"


int
main(void){

    //printf("\nBEGIN BMI UNIT TEST\n*******************\n");

    int status = BMI_SUCCESS;
    
    // Allocate model for bmi model struct
    // printf(" allocating memory for model structure...\n");
    Bmi *model = (Bmi *) malloc(sizeof(Bmi));

    // Register BMI model
    /* TODO: check if this bmi function needs to be model specific?
            or can be called 'regester_bmi()'?*/
    // printf(" registering BMI model...\n");
    register_bmi_topmodel(model);

    // Test BMI: CONTROL FUNCTION initialize()
    {
        //printf(" initializing...");
        const char *cfg_file = "./data/topmod_unit_test.run";
        //printf(" configuration found: %s\n", cfg_file);
        status = model->initialize(model, cfg_file);
        if (status == BMI_FAILURE) return BMI_FAILURE;
    }

    // Test BMI: MODEL INFORMATION FUNCTIONS
    printf("\nTEST BMI MODEL INFORMATION FUNCTIONS\n************************************\n");
    char name[BMI_MAX_COMPONENT_NAME];
    int count_in = 0;
    int count_out = 0;
    char **names_in = NULL;
    char **names_out = NULL;
    int i;

    // Test get_component_name()
/*    {
        status = model->get_component_name(model, name);
        if (status == BMI_FAILURE) return BMI_FAILURE;
        printf(" get_component_name(): %s\n", name);
    }*/
    // Test get_input_item_count()
    {
        status = model->get_input_item_count(model, &count_in);
        if (status == BMI_FAILURE ) return BMI_FAILURE;
        printf(" get_input_item_count(): %i\n", count_in);
    }
    

    // Test get_input_var_names()
    { 
        names_in = (char**) malloc (sizeof(char *) * count_in);
        for (i=0; i<count_in; i++)
            names_in[i] = (char*) malloc (sizeof(char) * BMI_MAX_VAR_NAME);
        status = model->get_input_var_names(model, names_in);
        if (status == BMI_FAILURE) return BMI_FAILURE;
        printf( " get_input_var_names():\n");
        for (i=0; i<count_in; i++)
            printf("   %s\n", names_in[i]);
        //free(names_in);
    }
    
    // Test get_output_item_count()
    {
        status = model->get_output_item_count(model, &count_out);
        if (status == BMI_FAILURE) return BMI_FAILURE;
        printf(" get_output_item_count(): %i\n", count_out);
    }
    // Test get_output_var_names()
    {
        names_out = (char**) malloc (sizeof(char *) * count_out);
        for (i=0; i<count_out; i++)
          names_out[i] = (char*) malloc (sizeof(char) * BMI_MAX_VAR_NAME);
        status = model->get_output_var_names(model, names_out);
        if (status == BMI_FAILURE) return BMI_FAILURE;
        printf( " get_output_var_names():\n");
        for (i=0; i<count_out; i++)
            printf("   %s\n", names_out[i]);
        //free(names_out);
    }


    // Test BMI: NEW ENHANCEMENTS
    printf("\nTEST BMI NEW ENHANCEMENTS\n*************************\n");
    //int count_all = 0; //state
    int count_model_var = 0; //""
    int count_tmp = 0; //loop
    int count_model_var_roles = 9;  // this is hard-coded for now
    //char **names_all = NULL; //state
    char **names_model_var = NULL; //""
    char **names_model_var_roles = NULL;
    char **names_tmp = NULL; //loop
    int j;
    // Test get_model_var_roles()
    { 
        names_model_var_roles = (char**) malloc (sizeof(char *) * count_model_var_roles);
        for (j=0; j<count_model_var_roles; j++)
            names_model_var_roles[j] = (char*) malloc (sizeof(char) * BMI_MAX_ROLE_NAME);
        status = model->get_model_var_roles(model, names_model_var_roles);
        if (status == BMI_FAILURE) return BMI_FAILURE;
        printf( " get_model_var_roles():\n");
        for (j=0; j<count_model_var_roles; j++)
            printf("  %s\n", names_model_var_roles [j]);
    }
    // Test get_model_var_count(some_role)
    for (j=0; j<count_model_var_roles; j++){
        {
            status = model->get_model_var_count(model, &count_model_var, names_model_var_roles [j]);
            if (status == BMI_FAILURE ) return BMI_FAILURE;
            printf(" get_model_var_count(%s): %i\n", names_model_var_roles [j], count_model_var);

        }
        // Test get_model_var_names(some_role)
        { 
            names_tmp = (char**) malloc (sizeof(char *) * count_model_var);
            for (i=0; i<count_model_var; i++)
                names_tmp[i] = (char*) malloc (sizeof(char) * BMI_MAX_VAR_NAME);
            status = model->get_model_var_names(model, names_tmp, names_model_var_roles [j]);
            if (status == BMI_FAILURE) return BMI_FAILURE;
            printf( " get_model_var_names(%s):\n", names_model_var_roles [j]);
            for (i=0; i<count_model_var; i++)
                printf("  %i %s\n", i, names_tmp[i]);
            free(names_tmp);
        }
    }
    

    free(names_model_var_roles); //don't need list of roles anymore
    // Check get_model_var_count("") when null string passed
    {
        status = model->get_model_var_count(model, &count_model_var, "");
        if (status == BMI_FAILURE ) return BMI_FAILURE;
        printf(" get_model_var_count(""): %i\n", count_model_var);
    }

/*    // Test get_state_var_count()
    {
        status = model->get_state_var_count(model, &count_all);
        if (status == BMI_FAILURE ) return BMI_FAILURE;
        printf(" state var count: %i\n", count_all);
    }
    // Test get_state_var_names()
    { 
        names_all = (char**) malloc (sizeof(char *) * count_all);
        for (i=0; i<count_all; i++)
            names_all[i] = (char*) malloc (sizeof(char) * BMI_MAX_VAR_NAME);
        status = model->get_state_var_names(model, names_all);
        if (status == BMI_FAILURE) return BMI_FAILURE;
        printf( " state variable names:\n");
        for (i=0; i<count_all; i++)
            printf("  %i %s\n", i, names_all[i]);
        //free(names_all);
    }*/

    // Test get_model_var_names()
    { 
        names_model_var = (char**) malloc (sizeof(char *) * count_model_var);
        for (i=0; i<count_model_var; i++)
            names_model_var[i] = (char*) malloc (sizeof(char) * BMI_MAX_VAR_NAME);
        status = model->get_model_var_names(model, names_model_var, "");
        if (status == BMI_FAILURE) return BMI_FAILURE;
        printf( " get_model_var_names(""):\n");
        for (i=0; i<count_model_var; i++)
            printf("  %i %s\n", i, names_model_var[i]);
        //free(names_model_var);
    }
/*    // Test get_model_var_names(input)
    { 
        names_in = (char**) malloc (sizeof(char *) * count_in);
        for (i=0; i<count_in; i++)
            names_in[i] = (char*) malloc (sizeof(char) * BMI_MAX_VAR_NAME);
        status = model->get_model_var_names(model, names_in, "input");
        if (status == BMI_FAILURE) return BMI_FAILURE;
        printf( " get_model_var_names(input):\n");
        for (i=0; i<count_in; i++)
            printf("  %i %s\n", i, names_in[i]);
        //free(names_in);
    }
    // Test get_model_var_names(output)
    { 
        names_out = (char**) malloc (sizeof(char *) * count_out);
        for (i=0; i<count_out; i++)
            names_out[i] = (char*) malloc (sizeof(char) * BMI_MAX_VAR_NAME);
        status = model->get_model_var_names(model, names_out, "output");
        if (status == BMI_FAILURE) return BMI_FAILURE;
        printf( " get_model_var_names(output):\n");
        for (i=0; i<count_out; i++)
            printf("  %i %s\n", i, names_out[i]);
        //free(names_out);
    }*/



    // Test BMI: VARIABLE INFORMATION FUNCTIONS
    printf("\nTEST BMI VARIABLE INFORMATION FUNCTIONS\n*****************************************\n");
    int grid, itemsize, nbytes;
    char type[BMI_MAX_TYPE_NAME];
    char location[BMI_MAX_LOCATION_NAME];
    char units[BMI_MAX_UNITS_NAME];
    char role[BMI_MAX_ROLE_NAME];

    // Loop through some variables and call get_var_*()
    for (i=28; i<37; i++){
        const char *var_name = names_model_var[i];
        printf( " %s\n", var_name);
        // Test get_var_grid()
        { 
            status = model->get_var_grid(model, var_name, &grid);
            if (status == BMI_FAILURE) return BMI_FAILURE;
            printf( "  get_var_grid(): %i\n", grid);
        }
        // Test get_var_itemsize()
        {
            status = model->get_var_itemsize(model, var_name, &itemsize);
            if (status == BMI_FAILURE) return BMI_FAILURE;
            printf( "  get_var_itemsize(): %i\n", itemsize);
        }
        { // Test get_var_location()
            status = model->get_var_location(model, var_name, location);
            if (status == BMI_FAILURE) return BMI_FAILURE;
            printf( "  get_var_location(): %s\n", location);
        }
        // Test get_var_units()
        { 
            status = model->get_var_units(model, var_name, units);
            if (status == BMI_FAILURE) return BMI_FAILURE;
            printf( "  get_var_units(): %s\n", units);
        }
        // Test get_var_type()
        { 
            status = model->get_var_type(model, var_name, type);
            if (status == BMI_FAILURE) return BMI_FAILURE;
            printf( "  get_var_type(): %s\n", type);
        }
        { // get_var_nbytes()
            status = model->get_var_nbytes(model, var_name, &nbytes);
            if (status == BMI_FAILURE) return BMI_FAILURE;
            printf( "  get_var_nbytes(): %i\n", nbytes);
        }
        { // Test get_var_role()
            status = model->get_var_role(model, var_name, role);
            if (status == BMI_FAILURE) return BMI_FAILURE;
            printf( "  get_var_role(): %s\n", role);
        }
    }

    // Test BMI: MODEL GRID FUNCTIONS
/*    printf("\nTEST BMI GRID FUNCTIONS\n***********************\n");
    int grid_id = 0; //TODO: impliment for multiple grids, for now we know 0
    int grid_rank, grid_size;
    char grid_type[BMI_MAX_COMPONENT_NAME];
    printf( " grid id %i\n", grid_id);
    // Test get_grid_rank()
    { 
        status = model->get_grid_rank(model, grid_id, &grid_rank);
        if (status == BMI_FAILURE) return BMI_FAILURE;
        printf ("  rank: %i\n",grid_rank);
    }
    // Test get_grid_size
    {
        status = model->get_grid_size(model, grid_id, &grid_size);
        if (status == BMI_FAILURE) return BMI_FAILURE;
        printf ("  size: %i\n",grid_size);
    }
    // Test get_grid_type
    {
        status = model->get_grid_type(model, grid_id, grid_type);
        if (status == BMI_FAILURE) return BMI_FAILURE;
        printf ("  type: %s\n",grid_type);
    }
    */

    // Test BMI: TIME FUNCTIONS
/*    printf("\nTEST BMI TIME FUNCTIONS\n***********************\n");
    double time = 0.0;
    double dt = 0.0;
    char units_time[BMI_MAX_UNITS_NAME];
    // Test get_start_time()
    {   
        status = model->get_start_time(model, &time);
        if (status == BMI_FAILURE) return BMI_FAILURE;
        printf(" start time: %f\n", time);
    }
    // Test get_end_time()
    {
        status = model->get_end_time(model, &time);
        if (status == BMI_FAILURE) return BMI_FAILURE;
        printf(" end time: %f\n", time);
    }
    // Test get_time_step()
    {
        status = model->get_time_step(model, &dt);
        if (status == BMI_FAILURE) return BMI_FAILURE;
        printf(" time step: %f\n", dt);
    }
    // Test get_time_units()
    {
        status = model->get_time_units(model, units_time);
        if (status == BMI_FAILURE) return BMI_FAILURE;
        printf(" time units: %s\n", units_time);
    }
    // Test get_current_time()
    {
        status = model->get_current_time(model, &time);
        if (status == BMI_FAILURE) return BMI_FAILURE;
        printf(" current time: %f\n", time);
    }*/

    // Test BMI: GET VALUE FUNCTIONS
    printf("\nTEST BMI GETTER SETTER FUNCTIONS\n********************************\n"); 
    int test_nstep=1;
    double now;
    printf(" updating... timesteps in test loop: %i\n", test_nstep);
    for (int n=1;n<=test_nstep;n++) // shorter time loop for testing
    {
        // Test BMI: CONTROL FUNCTION update()
        {
            status = model->update(model);
            if (status == BMI_FAILURE) return BMI_FAILURE;
        }
        // Print current time step - function already tested
        model->get_current_time(model, &now);
        printf("\n current time: %f\n", now);
        
        // Loop through both input and output variables and call get/set_value_*()
        for (i=0; i<count_in; i++){
            const char *var_name = names_in[i];
            printf( "  %s\n", var_name);
            int len = 1;
            double *var = NULL;
            int inds = 0;
            double *dest = NULL;
            // Test get_value() at each timestep
            {
                var = (double*) malloc (sizeof (double)*len);
                status = model->get_value(model, var_name, var);
                if (status == BMI_FAILURE) return BMI_FAILURE;
                printf("   get value: %f\n", var[0]);
                free(var);

            }
            // Test get_value_at_indices()
            { 
                dest = (double*) malloc (sizeof (double)*len);
                status = model->get_value_at_indices(model, var_name, dest, &inds, len);
                if (status == BMI_FAILURE) return BMI_FAILURE;
                printf("   get value at indices: %f\n",dest[0]);
                free(dest);
            }
            // Test get_value_ptr()
            {
                status = model->get_value_ptr(model, var_name, (void**)(&var));
                if (status == BMI_FAILURE)return BMI_FAILURE;
                printf("   get value ptr: %f\n",var);
            }
            // Go ahead and test set_value_*() for last time step here
            if (n == test_nstep){
                // Test BMI set_value()
                {    
                    double *var_new = NULL;
                    var_new = (double*) malloc (sizeof (double)*len);
                    var = (double*) malloc (sizeof (double)*len);
                    var_new[0] = 99.9;
                    status = model->set_value(model, var_name, var_new);
                    if (status == BMI_FAILURE)return BMI_FAILURE;
                    printf("   set value: %f\n",var_new[0]);
                    // get_value to see if changed
                    model->get_value(model, var_name, var);
                    printf("   new get value: %f\n", var[0]);
                    free(var);
                    free(var_new);
                }
                // Test BMI set_value_at_indices()
                {
                    double *dest_new = NULL;
                    dest_new = (double*) malloc (sizeof (double)*len);
                    dest = (double*) malloc (sizeof (double)*len);
                    dest_new[0] = 11.1;
                    status = model->set_value_at_indices(model, var_name, &inds, len, dest_new);
                    if (status == BMI_FAILURE)return BMI_FAILURE;
                    printf("   set value at indices: %f\n",dest_new[0]);
                    // get_value_at_indices to see if changed
                    model->get_value_at_indices(model, var_name, dest, &inds, len);
                    printf("   new get value at indices: %f\n", dest[0]);
                    free(dest);
                    free(dest_new);
                }
            }
        }
        for (i=0; i<count_out; i++){
            const char *var_name = names_out[i];
            printf( "  %s\n", var_name);
            int len = 1;
            double *var = NULL;
            int inds = 0;
            double *dest = NULL;
            // Test get_value() at each timestep
            {
                var = (double*) malloc (sizeof (double)*len);
                status = model->get_value(model, var_name, var);
                if (status == BMI_FAILURE) return BMI_FAILURE;
                printf("   get value: %f\n", var[0]);
                free(var);

            }
            // Test get_value_at_indices()
            { 
                dest = (double*) malloc (sizeof (double)*len);
                status = model->get_value_at_indices(model, var_name, dest, &inds, len);
                if (status == BMI_FAILURE) return BMI_FAILURE;
                printf("   get value at indices: %f\n",dest[0]);
                free(dest);
            }
            // Test get_value_ptr()
            {
                status = model->get_value_ptr(model, var_name, (void**)(&var));
                if (status == BMI_FAILURE)return BMI_FAILURE;
                printf("   get value ptr: %f\n",var);
            }
            // Go ahead and test set_value_*() for last time step here
            if (n == test_nstep){
                // Test BMI set_value()
                {    
                    double *var_new = NULL;
                    var_new = (double*) malloc (sizeof (double)*len);
                    var = (double*) malloc (sizeof (double)*len);
                    var_new[0] = -99.9;
                    status = model->set_value(model, var_name, var_new);
                    if (status == BMI_FAILURE)return BMI_FAILURE;
                    printf("   set value: %f\n",var_new[0]);
                    // get_value to see if changed
                    model->get_value(model, var_name, var);
                    printf("   new get value: %f\n", var[0]);
                    free(var);
                    free(var_new);
                }
                // Test BMI set_value_at_indices()
                {
                    double *dest_new = NULL;
                    dest_new = (double*) malloc (sizeof (double)*len);
                    dest = (double*) malloc (sizeof (double)*len);
                    dest_new[0] = -11.1;
                    status = model->set_value_at_indices(model, var_name, &inds, len, dest_new);
                    if (status == BMI_FAILURE)return BMI_FAILURE;
                    printf("   set value at indices: %f\n",dest_new[0]);
                    // get_value_at_indices to see if changed
                    model->get_value_at_indices(model, var_name, dest, &inds, len);
                    printf("   new get value at indices: %f\n", dest[0]);
                    free(dest);
                    free(dest_new);
                }
            }
        }
    }
    free(names_out);
    free(names_in); 

/*    // Test BMI: GET VALUE FUNCTIONS
    printf("\nTEST BMI GETTER SETTER FUNCTIONS\n********************************\n"); 
    int test_nstep=1;
    double now;
    printf(" updating... timesteps in test loop: %i\n", test_nstep);
    
    for (int n=1;n<=test_nstep;n++) // shorter time loop for testing
    {
        // Test BMI: CONTROL FUNCTION update()
        {
            status = model->update(model);
            if (status == BMI_FAILURE) return BMI_FAILURE;
        }
        // Print current time step - function already tested
        model->get_current_time(model, &now);
        printf("\n current time: %f\n", now);
        
        // Loop through both all variables and call get/set_value_*()
        //for (i=0; i<count_model_var; i++){
        for (i=0; i<1; i++){
            const char *var_name = names_model_var[i];
            printf( "  %s\n", var_name);
            int len = 1;
            double *var = NULL;
            int inds = 0;
            double *dest = NULL;
            // Test get_value() at each timestep
            {
                var = (double*) malloc (sizeof (double)*len);
                status = model->get_value(model, var_name, var);
                if (status == BMI_FAILURE) return BMI_FAILURE;
                printf("   get value: %f\n", var[0]);
                free(var);

            }
            // Test get_value_at_indices()
            { 
                dest = (double*) malloc (sizeof (double)*len);
                status = model->get_value_at_indices(model, var_name, dest, &inds, len);
                if (status == BMI_FAILURE) return BMI_FAILURE;
                printf("   get value at indices: %f\n",dest[0]);
                free(dest);
            }
            // Test get_value_ptr()
            {
                status = model->get_value_ptr(model, var_name, (void**)(&var));
                if (status == BMI_FAILURE)return BMI_FAILURE;
                printf("   get value ptr: %f\n",var);
            }
            // Go ahead and test set_value_*() for last time step here
            if (n == test_nstep){
                // Test BMI set_value()
                {    
                    double *var_new = NULL;
                    var_new = (double*) malloc (sizeof (double)*len);
                    var = (double*) malloc (sizeof (double)*len);
                    var_new[0] = 99.9;
                    status = model->set_value(model, var_name, var_new);
                    if (status == BMI_FAILURE)return BMI_FAILURE;
                    printf("   set value: %f\n",var_new[0]);
                    // get_value to see if changed
                    model->get_value(model, var_name, var);
                    printf("   new get value: %f\n", var[0]);
                    free(var);
                    free(var_new);
                }
                // Test BMI set_value_at_indices()
                {
                    double *dest_new = NULL;
                    dest_new = (double*) malloc (sizeof (double)*len);
                    dest = (double*) malloc (sizeof (double)*len);
                    dest_new[0] = 11.1;
                    status = model->set_value_at_indices(model, var_name, &inds, len, dest_new);
                    if (status == BMI_FAILURE)return BMI_FAILURE;
                    printf("   set value at indices: %f\n",dest_new[0]);
                    // get_value_at_indices to see if changed
                    model->get_value_at_indices(model, var_name, dest, &inds, len);
                    printf("   new get value at indices: %f\n", dest[0]);
                    free(dest);
                    free(dest_new);
                }
            }
        }
    }
    free(names_model_var);*/
    
    // Test BMI: CONTROL FUNCTION update_until()
    {
        int added_nstep=5;
        int total_nstep= added_nstep + test_nstep;
        printf("\n updating until... new total timesteps in test loop: %i\n", total_nstep);
        status = model->update_until(model,total_nstep);
        if (status == BMI_FAILURE) return BMI_FAILURE;
        // confirm updated current time
        model->get_current_time(model, &now);
        printf(" current time: %f\n", now);
    }
    // Test BMI: CONTROL FUNCTION finalize()
    {
        printf("\n finalizing...\n");
        status = model->finalize(model);
        if (status == BMI_FAILURE) return BMI_FAILURE;
        printf("\n******************\nEND BMI UNIT TEST\n\n");
    }
    return 0;
}
