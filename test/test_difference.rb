require "orocos"
Orocos.initialize

Orocos.run "data_analysis::Difference" => "diff" do
    task = Orocos::TaskContext.get "diff"
    task.configure
    task.start

    writer_minuend    = task.minuend.writer
    writer_subtrahend = task.subtrahend.writer
    reader            = task.difference.reader

    minuend    = Types.base.VectorXd.from_a [6,5,4]
    subtrahend = Types.base.VectorXd.from_a [1,2,3]

    while true
        writer_minuend.write minuend
        writer_subtrahend.write subtrahend

        sample = reader.read

        puts minuend.to_a.to_s + " - " + subtrahend.to_a.to_s + " = " + sample.to_a.to_s if sample

        sleep 0.1
    end
end
