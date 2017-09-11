require "orocos"
Orocos.initialize

Orocos.run "data_analysis::Difference"    => "diff",
           "data_analysis::EuclideanNorm" => "norm" do
    diff_task = Orocos::TaskContext.get "diff"
    norm_task = Orocos::TaskContext.get "norm"

    diff_task.configure
    norm_task.configure

    diff_task.difference.connect_to norm_task.input_data

    diff_task.start
    norm_task.start

    writer_minuend    = diff_task.minuend.writer
    writer_subtrahend = diff_task.subtrahend.writer
    reader            = norm_task.norm.reader

    minuend    = Types.base.VectorXd.from_a [6,5,4]
    subtrahend = Types.base.VectorXd.from_a [1,2,3]

    while true
        writer_minuend.write minuend
        writer_subtrahend.write subtrahend
        sample = reader.read

        puts "sqrt_err(" + minuend.to_a.to_s + " - " + subtrahend.to_a.to_s + ") = " + sample.to_s if sample

        sleep 0.1
    end
end
