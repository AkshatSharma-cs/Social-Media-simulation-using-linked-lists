#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 50
#define POST_LEN 200

// Linked list node for posts
typedef struct Post {
    char content[POST_LEN];
    struct Post* next;
} Post;

// Linked list node for friends
typedef struct Friend {
    char name[NAME_LEN];
    struct Friend* next;
} Friend;

// Linked list node for users
typedef struct User {
    char name[NAME_LEN];
    Post* posts;
    Friend* friends;
    struct User* next;
} User;

User* head = NULL;  // Head of user list

// Function to create a new user
User* createUser(const char* name) {
    User* newUser = (User*)malloc(sizeof(User));
    strcpy(newUser->name, name);
    newUser->posts = NULL;
    newUser->friends = NULL;
    newUser->next = NULL;
    return newUser;
}

// Add user to the list
void addUser(const char* name) {
    User* newUser = createUser(name);
    newUser->next = head;
    head = newUser;
    printf("User '%s' created successfully!\n", name);
}

// Find user by name
User* findUser(const char* name) {
    User* temp = head;
    while (temp) {
        if (strcmp(temp->name, name) == 0) return temp;
        temp = temp->next;
    }
    return NULL;
}

// Add friend to a user
void addFriend(User* user, const char* friendName) {
    if (!user) return;
    Friend* newFriend = (Friend*)malloc(sizeof(Friend));
    strcpy(newFriend->name, friendName);
    newFriend->next = user->friends;
    user->friends = newFriend;
    printf("%s is now friends with %s\n", user->name, friendName);
}

// Add post to a user
void addPost(User* user, const char* content) {
    if (!user) return;
    Post* newPost = (Post*)malloc(sizeof(Post));
    strcpy(newPost->content, content);
    newPost->next = user->posts;
    user->posts = newPost;
    printf("Post added for %s!\n", user->name);
}

// Display a single user
void displayUser(User* user) {
    if (!user) return;
    printf("\n--- User: %s ---\n", user->name);

    // Show friends
    printf("Friends: ");
    Friend* f = user->friends;
    if (!f) printf("None");
    while (f) {
        printf("%s ", f->name);
        f = f->next;
    }
    printf("\n");

    // Show posts
    printf("Posts:\n");
    Post* p = user->posts;
    if (!p) printf("No posts yet.\n");
    while (p) {
        printf("- %s\n", p->content);
        p = p->next;
    }
    printf("-----------------\n");
}

// Display all users
void displayAllUsers() {
    User* temp = head;
    if (!temp) {
        printf("No users registered yet.\n");
        return;
    }
    while (temp) {
        displayUser(temp);
        temp = temp->next;
    }
}

int main() {
    int choice;
    char name[NAME_LEN], friendName[NAME_LEN], content[POST_LEN];
    User* user;

    while (1) {
        printf("\n=== Social Media Menu ===\n");
        printf("1. Create User\n");
        printf("2. Add Friend\n");
        printf("3. Add Post\n");
        printf("4. View All Users\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                printf("Enter username: ");
                fgets(name, NAME_LEN, stdin);
                name[strcspn(name, "\n")] = 0;
                if (findUser(name)) {
                    printf("User already exists!\n");
                } else {
                    addUser(name);
                }
                break;

            case 2:
                printf("Enter your username: ");
                fgets(name, NAME_LEN, stdin);
                name[strcspn(name, "\n")] = 0;
                user = findUser(name);
                if (!user) {
                    printf("User not found!\n");
                    break;
                }
                printf("Enter friend's name: ");
                fgets(friendName, NAME_LEN, stdin);
                friendName[strcspn(friendName, "\n")] = 0;
                addFriend(user, friendName);
                break;

            case 3:
                printf("Enter your username: ");
                fgets(name, NAME_LEN, stdin);
                name[strcspn(name, "\n")] = 0;
                user = findUser(name);
                if (!user) {
                    printf("User not found!\n");
                    break;
                }
                printf("Enter post content: ");
                fgets(content, POST_LEN, stdin);
                content[strcspn(content, "\n")] = 0;
                addPost(user, content);
                break;

            case 4:
                displayAllUsers();
                break;

            case 5:
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
