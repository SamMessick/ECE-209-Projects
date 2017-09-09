/* ECE 209 Section 051
 *
 * This program provides the source code
 * for an auto-completion interface.
 *
 * Functions allow the user to add dictionaries,
 * individual words and context, as well as ask
 * for suggestions for partially-typed words based
 * on their similarity to dictionary words and
 * a context word immediately preceeding the typed
 * word. Functionality includes returning the number
 * of dictionary words, context words and currently
 * allocated bytes of memory from function use.
 *
 * A linked list stores dictionary words with additional
 * linked lists at each dictionary word node storing semantic
 * context words for the word. The dictionary is kept sorted through
 * insertion for ease of linear searching.
 *
 * Author: Sam Messick
 * Last Modified: July 21, 2017
 *
 * Preferred Grading Machine: EOS Linux
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "autocomplete.h"
#define WORD_LENGTH 50

typedef struct context_list  // List of context words for a dictionary word
{
  char word[WORD_LENGTH];   // Context word
  struct context_list* next; // Pointer to next context nodes
} Context_Node;

typedef struct word_list   // List of dictionary words
{
  char word[WORD_LENGTH];  // Dictionary word
  struct word_list* next;  // Pointer to next dictionary node
  struct context_list* prior;  // Pointer to context list for dictionary word
} Dictionary_Node;
Dictionary_Node* head = NULL;  // Dictionary head

unsigned int TotalMemoryUsed = 3*sizeof(unsigned int) + sizeof(Dictionary_Node*); // Total amount of memory used in bytes
unsigned int NumberOfDictionaryWords = 0;     // Number of dictionary words in use
unsigned int NumberOfContextWords = 0;        // Number of context words in use

// Add the words in file specified by filename to the
// auto-complete engine. This may be called multiple
// times with different filenames.  The words in the new
// file are appended to the existing list.  Duplicates are not
// allowed.
// Argument: filename - file with words that need to be added
//                      to the table
// Return value: 0: success
//               1: bad file name
// Appends items through sorted insertion
// to the Dictionary_Node head list
int AutoComplete_LoadDictionary(const char *filename)
{
  char w[WORD_LENGTH] = {0};  // Array for scanning dictionary words
  /* Initialize input file */
  FILE* file = fopen(filename, "r");
  if(file == NULL /* Invalid file name */)
    return 1;

  /* Scan in words from file */
  while(fscanf(file, "%s", w) == 1)
    AutoComplete_AddWord(w);

  fclose(file);
  return 0;
}

// Add a word to the autocomplete dictionary.  If the word is already
// present, it simply does nothing.
void AutoComplete_AddWord(const char *word)
{
  char w[WORD_LENGTH];  // Array for decapitalizing word
  strcpy(w, word);
  w[0] |= 0x20;

  Dictionary_Node* tmp = malloc(sizeof(Dictionary_Node)); // Temp node for storing new word in Dictionary
  strcpy(tmp->word, w);
  tmp->prior = NULL;

  Dictionary_Node* previous_dictionary_node;       // Previous node in Dictionary
  Dictionary_Node* current_dictionary_node = head; // Current node in Dictionary
  if(head)
    current_dictionary_node->word[0] |= 0x20;  // Make sure that current node is lowercase

  /* Check if Dictionary head is NULL
   * If so, initialize head.          */
  if(head == NULL)
  {
    head = tmp;
    tmp->next = NULL;
    TotalMemoryUsed += sizeof(Dictionary_Node);
    NumberOfDictionaryWords++;
  }
  /* Otherwise, insert word in alphabetic position in dictionary */
  else while(current_dictionary_node) {
    /* check if word is already in list */
    if(strcmp(current_dictionary_node->word, tmp->word) == 0)
    {
      free(tmp); // Deallocate tmp and exit
      return;
    }
    /* Check if word should be inserted */
    if(strcmp(tmp->word, current_dictionary_node->word) < 0)
    {

      /* Insert at head of list */
      if(current_dictionary_node == head)
      {
        tmp->next = head;
        head = tmp;
        TotalMemoryUsed += sizeof(Dictionary_Node);
        NumberOfDictionaryWords++;
        return;
      }

      /* Insert in middle of list */
      else {
        previous_dictionary_node->next = tmp;
        tmp->next = current_dictionary_node;
        TotalMemoryUsed += sizeof(Dictionary_Node);
        NumberOfDictionaryWords++;
        return;
      }
    }
    /* Insert at tail of list */
    if(current_dictionary_node->next == NULL)
    {
      current_dictionary_node->next = tmp;
      tmp->next = NULL;
      TotalMemoryUsed += sizeof(Dictionary_Node);
      NumberOfDictionaryWords++;
      return;
    }
    previous_dictionary_node = current_dictionary_node;   // Remember last examined node
    current_dictionary_node = current_dictionary_node->next;  // Advance in Dictionary
    if(current_dictionary_node)
      current_dictionary_node->word[0] |= 0x20;  // Ensure that next node is lowercase
  }
}

// Add context for a word to the autocomplete dictionary.  If the word
// is not already present, then add it. If the word is present, add
// prior to its context. If prior is already present, do not add it a
// second time.
void AutoComplete_AddContext(const char *word, const char * prior) {
  Context_Node* tmp_context = malloc(sizeof(Context_Node)); // Temp node for storing new context word in Dictionary
  char w[WORD_LENGTH]; // Holding array for decapitalizing word
  strcpy(w, word);
  w[0] |= 0x20;        // Ensure word is lowercase
  char p[WORD_LENGTH]; // Holding array for decapitalizing prior
  strcpy(tmp_context->word, prior);
  p[0] |= 0x20;        // Ensure prior is lowercase

  /* Begin search for Dictionary_Node at dictionary head */
  Dictionary_Node* current_dictionary_node = head;
  if(head)
    current_dictionary_node->word[0] |= 0x20; // Decapitalize head for accurate search

  /* Perform linear search on dictionary until word is found */
  while(current_dictionary_node->next && strcmp(current_dictionary_node->word, w)) {
    current_dictionary_node = current_dictionary_node->next;
    current_dictionary_node->word[0] |= 0x20; // Decapitalize words for accurate search
  }

  /* Word not in Dictionary */
  if(strcmp(current_dictionary_node->word, w)){
    AutoComplete_AddWord(word);
    /* Advance to newly allocated word node */
    current_dictionary_node = head;
    while(strcmp(current_dictionary_node->word, w))
      current_dictionary_node = current_dictionary_node->next;
  }
  /* Check if context words defined under word */
  if(current_dictionary_node->prior == NULL /* No context defined */) {
    current_dictionary_node->prior = tmp_context;
    tmp_context->next = NULL;
    TotalMemoryUsed += sizeof(Context_Node);
    NumberOfContextWords++;
    return;
  }
  /* Search context list for insertion point for prior */
  Context_Node* current_context_node = current_dictionary_node->prior;
  Context_Node* previous_context_node = NULL;
  while(current_context_node)
  {
    /* check if prior is already in context word list */
    if(strcmp(current_context_node->word, tmp_context->word) == 0)
    {
      /* If so, deallocate prior and exit */
      free(tmp_context);
      return;
    }
    /* Check if word should be inserted */
    if(strcmp(tmp_context->word, current_context_node->word) < 0)
    {
      /* Insert at context list head */
        if(current_context_node == current_dictionary_node->prior)
        {
          current_dictionary_node->prior = tmp_context;
          tmp_context->next = current_context_node;
          TotalMemoryUsed += sizeof(Context_Node);
          NumberOfContextWords++;
          return;
        } else
        { /* Insert in middle of context list */
          previous_context_node->next = tmp_context;
          tmp_context->next = current_context_node; TotalMemoryUsed += sizeof(Context_Node);
          NumberOfContextWords++;
          return;
        }
    }
    /* Prior not found; insert at tail of context list */
    if(current_context_node->next == NULL) {
      current_context_node->next = tmp_context;
      tmp_context->next = NULL;
      TotalMemoryUsed += sizeof(Context_Node);
      NumberOfContextWords++;
      return;
    }
    previous_context_node = current_context_node;   // Remember last examined node
    current_context_node = current_context_node->next;  // Advance in context list
    if(current_context_node)
      current_context_node->word[0] |= 0x20;  // Decapitalize words for accurate search
  }
}

// Return an integer specifying the total amount of memory
// used by the auto-completer.
// Arguments: None
// Return value: integer that specifies in bytes the amount
//               of memory used, including global/static variables.
int AutoComplete_TotalMemoryUsed()
{
  return TotalMemoryUsed;
}

// Return an integer specifying the total number of words
// added to the auto-completer.
int AutoComplete_NumberOfDictionaryWords()
{
  return NumberOfDictionaryWords;
}

// Return an integer specifying the total number of words
// used for semantic context.
int AutoComplete_NumberOfContextWords()
{
  return NumberOfContextWords;
}

// For a given partial word, return no more than size possible
// completions.
// Arguments: prompt - the beginning of a word to complete
//            prior -  a string with the word that came before it; it
//                     may be NULL, and if so, no context is needed
//                     for a match. Otherwise, the prior must be part
//                     of the context of all returned words.
//            completions - an array to store the completions inside
//            size_of_array - size of the completions array
//
// Return value: number of completions returned in the array; 0 means
//               nothing was returned
int AutoComplete_Suggestion(const char *partial_word, const char *prior, const char *completions[], int size_of_array)
{
  /* Check if input is valid */
  if(partial_word == NULL || !strcmp(partial_word, ""))
    return 0;
  int completions_index = 0;  // Index in completions array
  int context_flag = 1;       // Context included in parameters; include in suggestion matching
  if(prior == NULL || !strcmp(prior, ""))
    context_flag = 0;         // No context specified

  char tmp_word[WORD_LENGTH]; // holding array for manipulating words
  strcpy(tmp_word, partial_word);
  int is_capitalized = 0;
  /* Check if partial_word was capitalized */
  if((partial_word[0] & 0x20) == 0)
  {
    tmp_word[0] |= 32;        // ensure that partial word input is lowercase
    is_capitalized = 1;       // ensure that output suggestions are capitalized
  }

  /* Start suggestion search at dictionary head */
  Dictionary_Node* current_dictionary_node = head;
  Context_Node* current_context_node = NULL;

  /* Look for completions in a linear search of the dictionary */
  while(completions_index < size_of_array && current_dictionary_node)
  {
    int comp_index = 0;   // current character index to compare
    int match_flag = 0;   // Sentinel: whether or not partial_word matches current_dictionary_node

    /* Compare letters until end of partial_word is reached or a mismatch is found */
    while(current_dictionary_node->word[comp_index] == tmp_word[comp_index])
    {
      /* All characters in partial word match current word */
      if(tmp_word[comp_index + 1] == '\0')
      {
        match_flag++;
        break;
      }
      comp_index++;
    }

    /* No match found and completions have been made */
    if(!match_flag && completions_index)
      return completions_index;

    if(match_flag /* Match found */)
    {
      if(context_flag /* Context specified */)
      {
        /* Search context list for prior */
        current_context_node = current_dictionary_node->prior;
        while(current_context_node)
        {
          if(!strcmp(current_context_node->word, prior) /* Context found */)
          {
            if(is_capitalized)
            {
              /* Capitalize word, return suggestion in completions[]
               * and update completions index */
              current_dictionary_node->word[0] &= 0xFFDF;
              completions[completions_index] = current_dictionary_node->word;
              completions_index++;
              break;
            }
            else {
              /* Return suggestion and update completions index */
              completions[completions_index] = current_dictionary_node->word;
              completions_index++;
              break;
            }
          }
          /* Context not found; continue search */
          else current_context_node = current_context_node->next;
        }
      }
      /* No context specified */
      else
      {
        if(is_capitalized)
        {
          /* Capitalize word, return suggestion in completions[]
           * and update completions index */
          current_dictionary_node->word[0] &= 0xFFDF;
          completions[completions_index] = current_dictionary_node->word;
          completions_index++;
        }
        else
        {
          /* Return suggestion and update completions index */
          completions[completions_index] = current_dictionary_node->word;
          completions_index++;
        }
      }
    }
    /* Proceed to check next word in dictionary
     * Ensure that is lowercase for accurate search */
    current_dictionary_node = current_dictionary_node->next;
    if(current_dictionary_node)
      current_dictionary_node->word[0] |= 0x20;
  }
  /* End of dictionary or maximum number of completions reached */
  return completions_index;
}

int main() {
  const char* completions[1000];
  /*char* pointer = "hello";
  AutoComplete_AddWord("zebra");
  AutoComplete_AddWord(pointer);
  AutoComplete_AddWord("funtime");
  AutoComplete_AddWord("zebadiah");
  AutoComplete_AddContext("funtime", "glorious");
  AutoComplete_AddContext("Fudrucker", "magnificent");
  AutoComplete_AddContext("zebra", "white");
  AutoComplete_AddContext("zebra", "black");
  AutoComplete_AddContext("zebra", "blaq");
  printf("Number of suggestions found: %d\n\n", AutoComplete_Suggestion("zeb", "brown", completions, 2));


  char cc[100];
  char input[100]; */

  //int i;
  AutoComplete_LoadDictionary("input.txt");
  printf("\nTotal memory used in execution: %lf KB\n", ((double) TotalMemoryUsed)/1080);
  printf("\nTotal number of words: %d\n", NumberOfDictionaryWords);
  printf("\nTotal number of context words: %d\n\n", NumberOfContextWords);
  //while(list_current != NULL) { printf("%s\n", list_current->word);
  //  list_current = list_current->next;
  /*FILE* context = fopen("words.english.medium.context", "r"); while(fscanf(context, "%s%s", input, cc) == 2)
    AutoComplete_AddContext(input, cc);
    printf("\n\n\nTotal memory used in execution: %lf kilobytes\n", ((double) TotalMemoryUsed)/1080);
  printf("\nSuggestions for 'chan' = %d\n\n", AutoComplete_Suggestion("chan", NULL, completions, 10));
  printf("\nSuggestions for 'to S' = %d\n\n", AutoComplete_Suggestion("S", "to", completions, 10));
  for(i = 0; i < 10; i++) {
    printf("S could be: %s\n", completions[i]);
  }
  printf("\nSuggestions for 'to s' = %d\n\n", AutoComplete_Suggestion("s", "to", completions, 10));
  for(i = 0; i < 10; i++) {
    printf("s could be: %s\n", completions[i]);
  }
  printf("\nSuggestions for 'S' = %d\n\n", AutoComplete_Suggestion("S", "", completions, 200));
  for(i = 0; i < 185; i++) {
    printf("S could be: %s\n", completions[i]);
  }
  printf("\nSuggestions for 'xiphoidal' = %d\n\n", AutoComplete_Suggestion("xiphoidal", "", completions, 10));
  printf("\nTotal memory used in execution: %lf KB\n", ((double) TotalMemoryUsed)/1080);
  printf("\nTotal number of words: %d\n", NumberOfDictionaryWords);
  printf("\nTotal number of context words: %d\n\n", NumberOfContextWords); */
  return 0;
}
