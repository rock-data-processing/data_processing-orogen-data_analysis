require "orocos"
Orocos.initialize
Orocos.load_typekit("data_analysis")

Orocos.run "data_analysis::SigmoidTask" => "sigmoid" do
    task = Orocos::TaskContext.get "sigmoid"
    params = Types.data_analysis.SigmoidParams.new
    params.lower_asymptote = 0.0
    params.upper_asymptote        = 1.0
    params.growth_rate            = 1.0
    params.hor_shift              = 0.0
    params.initial_value          = 1.0
    task.sigmoid_params = params

    task.configure
    task.start

    writer = task.input_data.writer
    reader = task.sigmoid.reader

    input_data = -3.0
    step_size = 0.1
    output_data = []

    task.writeToFile("test_sigmoid.txt", input_data, -input_data, step_size)
    from_file = []
    File.foreach("test_sigmoid.txt") { |li| from_file << li.split(" ")[1].to_f }

    while output_data.size != from_file.size
        writer.write input_data
        sample = nil
        while !sample
            sample = reader.read_new
        end
        output_data << sample
        input_data += step_size
        sleep 0.1
    end

    print "Data from file: " + from_file.to_s + "\n\n"
    print "Data from output port: " + output_data.to_s + "\n\n"
end
