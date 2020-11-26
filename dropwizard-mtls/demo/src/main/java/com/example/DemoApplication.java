package com.example;

import io.dropwizard.Application;
import io.dropwizard.setup.Bootstrap;
import io.dropwizard.setup.Environment;

import java.io.File;

public class DemoApplication extends Application<DemoConfiguration> {

    public static void main(final String[] args) throws Exception {
	if (args.length > 0 && "client".equals(args[0]))
	{
		System.out.println("client");
		new DemoClient().run(new File("stores/ca.crt"), new File("stores/client_store"), "passphrase");
	}
	else
		new DemoApplication().run(args);
    }

    @Override
    public String getName() {
        return "Demo";
    }

    @Override
    public void initialize(final Bootstrap<DemoConfiguration> bootstrap) {
    }

    @Override
    public void run(final DemoConfiguration configuration,
                    final Environment environment) {
        final DemoResource resource = new DemoResource(configuration.getMessage());
        environment.jersey().register(resource);
    }
}
