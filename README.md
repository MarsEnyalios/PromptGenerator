# PromptGenerator
Generates random prompts

A NOTE ABOUT APPENDING: 

Special characters (speaking mainly of curved "s and 's; asteriks, em-dashes, and tildes appear to be just fine, so I assume other such characters are, but idk. You can test it out.) are not recognized as punctuation or letters. Nor are spaces or newlines. Therefore, the file you have for the propmts should be contiguous, with no spaces in front of each prompt (or else not all or the prompts will be read in!) and a single enter line at the end of each. 

      So
      Like
      "This"
      
      instead 
         of
         like
         
      this.

The first example will read out as 3 prompts saved. The second would only read out as 1 (the spaces or the empty line would block it).

You also must have an empty line at the bottom of the file, or else it will append to the end of the last prompt. 

      So, say
      you have a file
      like this

If you wanted to append "this" to the file as a separate prompt, it would end up like so: 

      So, say
      you have a file
      like this this

instead of:

      So, say
      you have a file
      like this
      this

My advice: append only from the prompt generator to avoid accidental errors. It drove me nuts trying to figure out why the append option would and wouldn't work at times. So, there you are. 
