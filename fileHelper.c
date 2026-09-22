#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "cJSON/cJSON.h"
#include "fileHelper.h"

bool jsonInit(char *firstName, char*lastName) {
    // create a cJSON object
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "firstName", firstName);
    cJSON_AddStringToObject(json, "lastName", lastName);

    // convert the cJSON object to a JSON string
    char *json_str = cJSON_Print(json);

    // write the JSON string to a file
    FILE *fp = fopen("data.json", "w");
    if (fp == NULL) {
        printf("Error: Unable to open the file.\n");
        cJSON_free(json_str);
        cJSON_Delete(json);
        return false;
    }

    fputs(json_str, fp);
    fclose(fp); // Fixed: added (fp)

    // free the JSON string and cJSON object
    cJSON_free(json_str);
    cJSON_Delete(json);
    return true;
}

bool checkName(char *firstNameMain, size_t firstNameCapacity,
               char *lastNameMain, size_t lastNameCapacity)
{
    FILE *fp = fopen("data.json", "r");
    if (fp == NULL)
        return false;

    char buffer[1024];
    size_t length = fread(buffer, 1, sizeof buffer - 1U, fp);
    buffer[length] = '\0';
    fclose(fp);

    cJSON *json = cJSON_Parse(buffer);
    if (json == NULL)
        return false;

    cJSON *firstName =
        cJSON_GetObjectItemCaseSensitive(json, "firstName");
    cJSON *lastName =
        cJSON_GetObjectItemCaseSensitive(json, "lastName");

    if (!cJSON_IsString(firstName) || firstName->valuestring == NULL ||
        !cJSON_IsString(lastName) || lastName->valuestring == NULL)
    {
        cJSON_Delete(json);
        return false;
    }

    size_t firstNameLength = strlen(firstName->valuestring);
    size_t lastNameLength = strlen(lastName->valuestring);

    if (firstNameLength == 0 || lastNameLength == 0 || firstNameLength >= firstNameCapacity ||
        lastNameLength >= lastNameCapacity)
    {
        cJSON_Delete(json);
        return false;
    }

    memcpy(firstNameMain, firstName->valuestring, firstNameLength + 1U);
    memcpy(lastNameMain, lastName->valuestring, lastNameLength + 1U);

    cJSON_Delete(json);
    return true;
}
