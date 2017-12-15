require "orocos"
Orocos.initialize
Orocos.conf.load_dir(".")

Orocos.run "data_analysis::Sigmoid" => "sigmoid" do
    task = Orocos::TaskContext.get "sigmoid"
    Orocos.conf.apply(task, ["default"])
    task.configure
    task.start

    writer = task.double.writer
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
        output_data << sample[0]
        input_data += step_size
        sleep 0.1
    end

    print "Data from file: " + from_file.to_s + "\n\n"
    print "Data from output port: " + output_data.to_s + "\n\n"
end
