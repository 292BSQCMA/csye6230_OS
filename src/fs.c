#include "../include/fs.h"
#include "../include/string.h"
#include "../include/stdlib.h"
#include "../include/serial.h"
#include "../include/fb.h"

fs_node_t *fs_root = NULL;
fs_node_t *fs_current = NULL;

void fs_init() {
    fs_root = (fs_node_t*)malloc(sizeof(fs_node_t));
    if (fs_root != NULL) {
        strcpy(fs_root->name, "/");
        fs_root->is_directory = 1;
        fs_root->parent = NULL;
        fs_root->num_children = 0;
        fs_current = fs_root;
    }
}

fs_node_t* fs_find(const char *name, fs_node_t *parent) {
    for (unsigned int i = 0; i < parent->num_children; i++) {
        if (strcmp(parent->children[i]->name, name) == 0) {
            return parent->children[i];
        }
    }
    return NULL;
}

void fs_create(const char *name, fs_node_t *parent) {
    if (parent->num_children >= FS_MAX_FILES) return;

    fs_node_t *new_node = (fs_node_t*)malloc(sizeof(fs_node_t));
    if (new_node != NULL) {
        strcpy(new_node->name, name);
        new_node->is_directory = 0;
        new_node->parent = parent;
        new_node->num_children = 0;

        parent->children[parent->num_children++] = new_node;
    }
}

void fs_delete(const char *name, fs_node_t *parent) {
    for (unsigned int i = 0; i < parent->num_children; i++) {
        if (strcmp(parent->children[i]->name, name) == 0) {
            free(parent->children[i]);
            for (unsigned int j = i; j < parent->num_children - 1; j++) {
                parent->children[j] = parent->children[j + 1];
            }
            parent->num_children--;
            return;
        }
    }
}

void fs_move(const char* src, const char* dest, fs_node_t* parent) {
    fs_node_t* node_to_move = fs_find(src, parent);
    if (node_to_move == NULL) {
        write("Source file/directory not found.\n", 32);
        return;
    }

    // Find destination directory
    fs_node_t* dest_dir = fs_find(dest, parent);
    if (dest_dir == NULL || !dest_dir->is_directory) {
        write("Destination must be a valid directory.\n", 36);
        return;
    }

    // Remove node from current parent's children
    for (unsigned int i = 0; i < parent->num_children; i++) {
        if (parent->children[i] == node_to_move) {
            for (unsigned int j = i; j < parent->num_children - 1; j++) {
                parent->children[j] = parent->children[j + 1];
            }
            parent->num_children--;
            break;
        }
    }

    // Add node to destination directory
    if (dest_dir->num_children < FS_MAX_FILES) {
        dest_dir->children[dest_dir->num_children++] = node_to_move;
        node_to_move->parent = dest_dir;
    }
    else {
        write("Destination directory is full.\n", 30);
    }
}

void fs_mkdir(const char *name, fs_node_t *parent) {
    if (parent->num_children >= FS_MAX_FILES) return;

    fs_node_t *new_node = (fs_node_t*)malloc(sizeof(fs_node_t));
    if (new_node != NULL) {
        strcpy(new_node->name, name);
        new_node->is_directory = 1;
        new_node->parent = parent;
        new_node->num_children = 0;

        parent->children[parent->num_children++] = new_node;
    }
}

void fs_ls(fs_node_t *parent) {
    for (unsigned int i = 0; i < parent->num_children; i++) {
        if (parent->children[i]->is_directory) {
            serial_write(parent->children[i]->name, strlen(parent->children[i]->name));
            serial_write("/\n", 2);
            write(parent->children[i]->name, strlen(parent->children[i]->name));
            write("/\n", 2);
        } else {
            serial_write(parent->children[i]->name, strlen(parent->children[i]->name));
            serial_write("\n", 1);
            write(parent->children[i]->name, strlen(parent->children[i]->name));
            write("\n", 1);
        }
    }
}

void fs_pwd(fs_node_t *node) {
    if (node->parent != NULL) {
        fs_pwd(node->parent);
    }
    serial_write(node->name, strlen(node->name));
    write(node->name, strlen(node->name));
    if (node->parent != NULL) {
        serial_write("/", 1);
        write("/", 1);
    }
}

void fs_cd(const char *name) {
    if (strcmp(name, "..") == 0 && fs_current->parent != NULL) {
        fs_current = fs_current->parent;
    } else {
        fs_node_t *new_dir = fs_find(name, fs_current);
        if (new_dir != NULL && new_dir->is_directory) {
            fs_current = new_dir;
        }
    }
}
