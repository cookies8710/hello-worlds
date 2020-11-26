package com.example;

import io.dropwizard.Configuration;
import com.fasterxml.jackson.annotation.JsonProperty;
import org.hibernate.validator.constraints.*;

public class DemoConfiguration extends Configuration {
    @NotEmpty
    private String message;

    @JsonProperty
    public String getMessage()
    {
	    return message;
    }

    @JsonProperty
    public void setMessage(String message)
    {
	    this.message = message;
    }
}
