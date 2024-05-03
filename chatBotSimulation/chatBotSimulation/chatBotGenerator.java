
//816034711

public class chatBotGenerator
{ 
    
    public String generateChatBotLLM(int LLMCodeNumber)
    {
        String botName = " ";
        if(LLMCodeNumber == 0 || LLMCodeNumber > 5)
        {
            botName = "ChatGPT-3.5";
        }
        
        if(LLMCodeNumber == 1)
        {
            botName = "LLaMa";
        }
        
        if(LLMCodeNumber == 2)
        {
            botName = "Mistral7B";
        }
        
        if(LLMCodeNumber == 3)
        {
            botName = "Bard";
        }
        
        if(LLMCodeNumber == 4)
        {
            botName = "Claude";
        }
        
        if(LLMCodeNumber == 5)
        {
            botName = "Solar";
        }
        return botName;
    }
    
    public String generateChatBotLLM(String botName) {return botName;}
}